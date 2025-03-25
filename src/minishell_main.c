/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:41:42 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 12:26:27 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_type(t_minishell *data)
{
	t_token *token;

	token = data->token_list;
	while (token)
	{
//		ft_printf("%d\n", token->type);
		if (token->type == 0)
			ft_printf("WORD\n");
		if (token->type == 1)
			ft_printf("COMMAND\n");
		if (token->type == 2)
			ft_printf("ARGUMENT\n");
		if (token->type == 3)
			ft_printf("BUILTIN\n");
		if (token->type == 4)
			ft_printf("PIPE\n");
		if (token->type == 5)
			ft_printf("REDIRECT_INPUT\n");
		if (token->type == 6)
			ft_printf("REDIRECT_OUTPUT\n");
		if (token->type == 7)
			ft_printf("HEREDOC\n");
		if (token->type == 8)
			ft_printf("APPEND\n");
		token = token->next;
	}
}

int	count_redirections(t_minishell *data)
{	
	t_token *token;
	int	count;

	token = data->token_list;
	count = 0;
	while (token)
	{
		if (token->type >= 4 && token->type <= 8)
			count++;
		token = token->next;
	}
	return (count);
}

int	builtin_check(t_minishell *data)
{
	t_token *token;
	token = data->token_list;
	while (token)
	{
		if (check_if_builtin(token->value) == 0)
		{
			printf("builtin token detected\n");
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	data;
	char	*shell_dir;
	char	*buffer;
	char	**envp_arr;

	(void)argc;
	(void)argv;
	data.arena = ft_new_memarena();
	if (!data.arena)
		return (ERROR_ALLOC);
	// Lets parse the enviroment variables to a list here
	parse_env(&data, envp);
	//lets start the readline loop.
	while (1)
	{
		//Setting the prompt to be the current dir so that it updates
		buffer = getcwd(NULL, 0);
		shell_dir = ft_ma_strjoin(data.arena, "mini_shell: ", buffer);
		shell_dir = ft_ma_strjoin(data.arena, shell_dir, "$ ");
		data.raw_input	= readline(shell_dir);
		//exit case (technically a builtin)
		if (ft_strncmp(data.raw_input, "exit", 4) == 0)
		{
			ft_putendl("exiting program");
			free((void *)data.raw_input);
			break ;
		}
		add_history(data.raw_input);
		lex_raw_input(&data);
		variable_expansion(&data);
		quote_removal(&data);
//		print_tokens(&data);
		print_tokens_type(&data);

		//Checking for builtins (rewrite when tokenizer type is present)
		if (builtin_check(&data) == 0)
		{
			printf("builtin detected\n");
			reroute_builtin(&data, data.token_list->value, data.custom_env);
		}
		else
		{
			//Runs a program
			envp_arr = create_envp_arr_from_custom_env(&data, data.custom_env);
			run_prog(&data, data.raw_input, envp_arr);
		}
		//need to check how many pipes are needed.

		printf("number of redirections is %d\n", count_redirections(&data));
		data.token_list = NULL;
		free((void *)data.raw_input);
	}
	ft_free_memarena(data.arena);
	return (0);
}
