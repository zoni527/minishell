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
#include <unistd.h>

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

int	count_redirections(t_minishell *data)
{	
	t_token *token;
	int	count;

	token = data->token_list;
	count = 0;
	while (token)
	{
		if (token->type >= 6 && token->type <= 9)
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

t_token	*check_and_get_here_doc_token(t_minishell *data)
{
	t_token *token;

	token = data->token_list;
	while (token)
	{
		if(token->type == HEREDOC)
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}

t_token *return_first_pipe_token(t_minishell *data)
{
	t_token *token;

	token = data->token_list;
	while (token)
	{
		if (token->type == PIPE)
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}

/**
 * Function that creates a null terminated argv to pass to execve
 *
 * @param data	main data struct
 * @param command	token for the relevant command
 */
char	**create_args_arr(t_minishell *data, t_token *command)
{
	char	**args;
	t_token *token;
	int		count;
	int		i;

	token = command;
	count = 1;
	while (token->next && token->next->type == ARGUMENT)
	{
		count++;
		token = token->next;
	}
	args = ft_ma_malloc(data->arena, sizeof(char *) * (count + 1));
	i = -1;
	token = command;
	while (++i < count)
	{
		args[i] = ft_ma_strdup(data->arena, token->value);
		token = token->next;
	}
	args[count] = NULL;

	// This can be deleted after debugging, just prints args for reference.
	i = 0;
	printf("print out of args:\n");
	while (i < count + 1)
	{
		if (args[i] == NULL)
			printf("args[%d] = NULL\n", i);
		else
			printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
	return (args);
	
}

t_token	*get_cmd_token(t_minishell *data)
{
	t_token	*token;
	token = NULL;

	token = data->token_list;
	while (token)
	{
		if (token->type == COMMAND)
		{
			return (token);
		}
		token = token->next;
	}
	return (NULL);
}

//args = create_args_arr(&data, command_token->value, command_token->next->value)
//

t_token *get_next_pipe_token(t_token *token)
{
//	printf("ONE\n");
	if (token->next)
	{
		token = token->next;
	}
	else
	{
		return (NULL);
	}
	while (token)
	{	
		if (token->type == PIPE)
		{
			printf("found pipe\n");
			return (token);
		}
		token = token->next;
	}
	printf("no pipe found\n");
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	data;
	char	*shell_dir;
	char	*buffer;
	char	**envp_arr;
	char	**args;
	t_token	*here_doc_token;

	(void)argc;
	(void)argv;
	here_doc_token = NULL;
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
//		data.raw_input = NULL;
		data.raw_input	= readline(shell_dir);
		if (!data.raw_input)
		{
			printf("readline failed...exiting..\n");
			free(buffer);
			break ;
		}
		if (ft_strlen(data.raw_input) == 0)
		{
			free((void *)data.raw_input);
			printf("loop reset\n");
			continue ;
		}
//		printf("raw_input: %s\n", data.raw_input);
		//exit case (technically a builtin)
		if (ft_strncmp(data.raw_input, "exit", 4) == 0)
		{
			ft_putendl("exiting program");
			free((void *)data.raw_input);
			free(buffer);
			break ;
		}
		add_history(data.raw_input);
		//==========================TOKENIZATION===============================*/
//		lex_raw_input(&data);
		tokenization(&data);
		variable_expansion(&data);
		word_splitting(&data);
		quote_removal(&data);
//		print_tokens(&data);
		print_tokens_type(&data);

		//==========================BUILT INS===================================*/
		here_doc_token = check_and_get_here_doc_token(&data);
		//Checking for builtins (rewrite when tokenizer type is present)
		if (builtin_check(&data) == 0)
		{
			printf("builtin detected\n");
			reroute_builtin(&data, data.token_list->value, data.custom_env);
		}
//		here_doc_token = check_and_get_here_doc_token(&data);
		//===========================HERE DOC===================================*/
		else if (here_doc_token != NULL)
		{
			if (here_doc_token->next == NULL)
				printf("error case\n");
			else
			{	
				printf("entering here_doc\n");
				here_doc(&data, here_doc_token->next->value);
			}
		}
		//========================REDIRECTION===================================*/
		else if (data.token_list->type == REDIRECT_INPUT)
		{
			if (data.token_list->next->type == FILE_NAME)
			{
				handle_infile(&data, data.token_list->next->value);
			}
//			t_token	command_token = *data.token_list->next->next;
			t_token	*command_token;
			command_token = get_cmd_token(&data);
			printf("COMMMAND TOKEN ASSIGNED\n");
			if (command_token != NULL)
			{
				printf("COMMAND FOUND\n");
				envp_arr = create_envp_arr_from_custom_env(&data, data.custom_env);
				args = create_args_arr(&data, command_token);
				run_prog(&data, args, envp_arr);
//				child_process_pipe(&data, args, envp_arr);
			}
			else
			{
				printf("COMMAND NOT FOUND\n");
			}
			// We need to return stdout to its natural state. and close it in the struct
			if (data.fd_in > 0)
			{
//				printf("reseting FD_IN to 0...\n");
				close (data.fd_in);
				dup2(data.std_in, STDIN_FILENO);
				close(data.fd_in);
			}
		}
		//======================= PIPES ===================================*/
		t_token	*token;
		token = data.token_list;
		while (token)
		{
//			int	i = 0;
			token = get_next_pipe_token(token);
			if (token == NULL)
				break ;
//			i++;
//			printf("FOUND PIPE %d\n", i);
			envp_arr = create_envp_arr_from_custom_env(&data, data.custom_env);
			args = create_args_arr(&data, token->next);
			printf("TWO\n");
			child_process_pipe(&data, args, envp_arr);
//			token = get_next_pipe_token(token);
		}
		// We need to return stdout to its natural state. and close it in the struct
		if (data.fd_in > 0)
		{
//			printf("reseting FD_IN to 0...\n");
			close (data.fd_in);
			dup2(data.std_in, STDIN_FILENO);
			close(data.fd_in);
		}

		//========================RUN PROGRAM===================================*/
		if(data.token_list->type == COMMAND)
		{
			//Runs a program
			printf("running program\n");
			envp_arr = create_envp_arr_from_custom_env(&data, data.custom_env);
			args = create_args_arr(&data, data.token_list);
			run_prog(&data, args, envp_arr);
//			printf("entering child process pipe\n");
//			child_process_pipe(&data, args, envp_arr);
		}
		//need to check how many pipes are needed.
		printf("number of redirections is %d\n", count_redirections(&data));
		data.token_list = NULL;
//		printf("token_list resest\n");
		free((void *)data.raw_input);
//		printf("readline reset\n");
		free(buffer);
//		data.raw_input = NULL;
	}
	//Free memory arena here
	ft_free_memarena(data.arena);
	return (0);
}
