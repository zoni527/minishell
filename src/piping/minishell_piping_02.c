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
static void	ignore_sigpipe(void);

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
	t_token	*command;

	safe_close(data, &data->extra_fd);
	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
	if (handle_redirections(data) == EXIT_FAILURE)
		clean_exit(data, EXIT_FAILURE);
	command = copy_cmd_and_args_within_pipe(data);
	if (!command)
		clean_exit(data, EXIT_SUCCESS);
	if (is_builtin(command))
		run_builtin_within_pipe(data, command);
	argv = create_args_arr(data, command);
	envp = create_envp_arr_from_custom_env(data);
	cmd_exec(data, argv, envp);
}

/**
 * Function to select correct builtin and run it in the current child process,
 * clean_error_exits if type can't be matched.
 *
 * @param data		Pointer to main data struct
 * @param builtin	Token to match
 *
 * @return	The return value of the builtin that was run
 */
static void	run_builtin_within_pipe(t_minishell *data, t_token *builtin)
{
	ignore_sigpipe();
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

static void	ignore_sigpipe(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGPIPE);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &sa, NULL);
}
