/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/02 14:20:28 by jvarila          ###   ########.fr       */
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
void	child_process(t_minishell *data, int extra_fd)
{
	char	**argv;
	char	**envp;
	t_token	*command;

	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
	{
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
		safe_close(data, &extra_fd);
	}
	if (handle_redirections(data) == EXIT_FAILURE)
		clean_exit(data, EXIT_FAILURE);
	command = skip_to(skip_to_current_pipe(data), is_builtin_or_command);
	if (!command)
		clean_exit(data, EXIT_SUCCESS);
	if (is_builtin(command))
		run_builtin_within_pipe(data, command);
	argv = create_args_arr(data, command);
	envp = create_envp_arr_from_custom_env(data, data->minishell_env);
	cmd_exec(data, argv, envp);
}

static void	run_builtin_within_pipe(t_minishell *data, t_token *builtin)
{
	if (get_builtin_type(builtin) == BLTN_CD)
		builtin_cd(data);
	else if (get_builtin_type(builtin) == BLTN_ECHO)
		builtin_echo(data);
	else if (get_builtin_type(builtin) == BLTN_ENV)
		builtin_env(data);
	else if (get_builtin_type(builtin) == BLTN_EXIT)
		builtin_exit(data);
	else if (get_builtin_type(builtin) == BLTN_EXPORT)
		builtin_export(data);
	else if (get_builtin_type(builtin) == BLTN_PWD)
		builtin_pwd(data);
	else if (get_builtin_type(builtin) == BLTN_UNSET)
		builtin_unset(data);
	else
		clean_error_exit(data, MSG_ERROR_BLTN_NOSUCH, EXIT_BLTN_NOSUCH);
	clean_exit(data, data->last_rval);
}
