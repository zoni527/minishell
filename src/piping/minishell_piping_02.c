/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 13:34:57 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin_within_pipe(t_minishell *data, t_token *command);

/**
 * Main child process function. Handles pipe reading and writing, input and
 * output redirections, heredocs, execution setup and execution.
 *
 * @param data	Pointer to main data struct
 */
void	child_process(t_minishell *data)
{
	char	**argv;
	char	**envp;
	t_token	*tokens;
	t_token	*command;

	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
	if (handle_redirections(data) == EXIT_FAILURE)
		return ;
	tokens = skip_to_current_pipe(data);
	command = copy_cmd_and_args_within_pipe(data, tokens);
	if (is_builtin(command))
		run_builtin_within_pipe(data, command);
	argv = create_args_arr(data, command);
	envp = create_envp_arr_from_custom_env(data, data->minishell_env);
	cmd_exec(data, argv, envp);
	ft_putendl_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	exit (EXIT_EXECVE);
}

static void	run_builtin_within_pipe(t_minishell *data, t_token *builtin)
{
	if (get_builtin_type(builtin) == BLTN_CD)
		builtin_cd(data, builtin);
	else if (get_builtin_type(builtin) == BLTN_ECHO)
		builtin_echo(data, builtin);
	else if (get_builtin_type(builtin) == BLTN_ENV)
		builtin_env(data);
	else if (get_builtin_type(builtin) == BLTN_EXIT)
		builtin_exit(data, builtin);
	else if (get_builtin_type(builtin) == BLTN_EXPORT)
		builtin_export(data, builtin);
	else if (get_builtin_type(builtin) == BLTN_PWD)
		builtin_pwd(data);
	else if (get_builtin_type(builtin) == BLTN_UNSET)
		builtin_unset(data, builtin);
	else
		clean_error_exit(data, MSG_ERROR_BLTN_NOSUCH, EXIT_BLTN_NOSUCH);
	exit(data->last_rval);
}
