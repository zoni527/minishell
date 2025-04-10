/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_builtins.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:06:35 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:35 by rhvidste         ###   ########.fr       */
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
		if (token->type == WORD)
			ft_printf("WORD\n");
		if (token->type == COMMAND)
			ft_printf("COMMAND\n");
		if (token->type == ARGUMENT)
			ft_printf("ARGUMENT\n");
		if (token->type == BUILTIN)
			ft_printf("BUILTIN\n");
		if	(token->type == FILE_NAME)
			ft_printf("FILE_NAME\n");
		if (token->type == PIPE)
			ft_printf("PIPE\n");
		if (token->type == REDIRECT_INPUT)
			ft_printf("REDIRECT_INPUT\n");
		if (token->type == REDIRECT_OUTPUT)
			ft_printf("REDIRECT_OUTPUT\n");
		if (token->type == HEREDOC)
			ft_printf("HEREDOC\n");
		if (token->type == APPEND)
			ft_printf("APPEND\n");
		token = token->next;
	}
}

void	print_env(t_minishell *data)
{
	t_var	*token;
	token = data->minishell_env;
	while (token)
	{
		ft_putendl_fd(token->value, 1);
		token = token->next;
	}
			
}

void	loop(t_minishell *data)
{
	char	*line;
	char	*buffer;
	char	*shell_dir;

	while (1)
	{
		buffer = getcwd(NULL, 0);
		shell_dir = ft_ma_strjoin(data->arena, "mini_shell: ", buffer);
		shell_dir = ft_ma_strjoin(data->arena, shell_dir, "$ ");
		data->raw_input = readline(shell_dir);
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free((void *)data->raw_input);
			break ;
		}
		if (has_unclosed_quotes(data->raw_input))
		{
			ft_putendl("Input has unclosed quotes");
			free((void *)data->raw_input);
			continue ;
		}
		tokenization(data);
//		print_env(data);
		print_tokens_type(data);
		//implament built in detection.
		builtin_handler(data);		
//		piping(data);
		printf("last exit value is %d\n", data->last_rval);
		add_history(data->raw_input);
		data->token_list = NULL;
		free((void *)data->raw_input);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	static t_minishell	data;

	(void)argc;
	(void)argv;
//	(void)envp;
	data.arena = ft_new_memarena();
	data.initial_env = (const char **)envp;
	env_list_from_envp(&data, (char **)data.initial_env);
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
