/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:32:51 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/08 10:21:59 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_new_pipe_and_assign_fds(t_minishell *data, int *new_pipe, \
									int prev_pipe_read_fd);
static void	handle_fork_failure(t_minishell *data, int *new_pipe, \
						int prev_pipe_read_fd);
static void	close_pipe_fds_in_parent(t_minishell *data, int *new_pipe, \
									int *prev_pipe_read_fd);
static void	wait_for_children(t_minishell *data);

/**
 * Creates pipes, forks, and waits for child processes.
 * <p>
 * If a fork or file descriptor redirection fails, subfunctions will call a
 * cleanup and exit function.
 *
 * @param data	Pointer to main data struct
 */
void	piping(t_minishell *data)
{
	int		new_pipe[2];
	int		prev_pipe_read_fd;

	data->pipe_index = 0;
	data->last_pid = 1;
	prev_pipe_read_fd = -1;
	while (data->pipe_index <= data->pipe_count && data->last_pid != 0)
	{
		create_new_pipe_and_assign_fds(data, new_pipe, prev_pipe_read_fd);
		data->last_pid = fork();
		if (data->last_pid < 0)
			handle_fork_failure(data, new_pipe, prev_pipe_read_fd);
		else if (data->last_pid == 0)
			break ;
		else if (data->last_pid != 0)
			close_pipe_fds_in_parent(data, new_pipe, &prev_pipe_read_fd);
		prev_pipe_read_fd = new_pipe[READ];
		data->pipe_index++;
	}
	if (data->last_pid == 0)
		child_process(data);
	else
		wait_for_children(data);
}

/**
 * Creates new pipe, the fork currently being created will write into the new
 * pipe's write end and read from the previously created pipe's read end, if
 * a previous pipe exists.
 *
 * @param data				Pointer to main data struct
 * @param new_pipe			Pointer to int[2], target for pipe function
 * @param prev_pipe_read_fd	File descriptor value of previously created pipe's
 *							read end, -1 if previous pipe doesn't exist
 * @see   safe_pipe
 */
static void	create_new_pipe_and_assign_fds(t_minishell *data, int *new_pipe, \
									int prev_pipe_read_fd)
{
	if (data->pipe_index != data->pipe_count)
		safe_pipe(data, new_pipe);
	if (prev_pipe_read_fd != -1)
		data->pipe_fds[READ] = prev_pipe_read_fd;
	if (data->pipe_index != data->pipe_count)
		data->pipe_fds[WRITE] = new_pipe[WRITE];
}

/**
 * Waits for child processes, data->pipe_index is used instead of
 * data->pipe_count to account for situations when not all pipes are created.
 * Sets data->last_rval to match the exit value of the last child's exit value.
 *
 * @param data	Pointer to main data struct
 */
static void	wait_for_children(t_minishell *data)
{
	size_t	children;
	pid_t	pid;

	(void)pid;
	children = data->pipe_index + 1;
	while (children--)
	{
		pid = wait(NULL);
		if (pid == data->last_pid)
		{
			if (WIFEXITED(pid))
				data->last_rval = WEXITSTATUS(pid);
			else if (g_signal != 0)
			{
				data->last_rval = 128 + g_signal;
				g_signal = 0;
			}
			else
				data->last_rval = -2;
		}
	}
}

/**
 * Closes pipe fds in parent process. Doesn't close write end if the last
 * chils process has been created, because that process won't have a new
 * pipe to write to. Similarly doesn't close prev_pipe_read_fd if there is
 * only one child created at that point (pipe_index start at 0 and goes
 * until pipe_count, so one more process than the amount of pipes will be
 * created, cmd0 | cmd1 | cmd2).
 *
 * @param data				Pointer to main data struct
 * @param new_pipe			Pointer to int[2], target for pipe function
 * @param prev_pipe_read_fd	Pointer to file descriptor value of previously
 *							created pipe's read end
 * @see   safe_close
 */
static void	close_pipe_fds_in_parent(t_minishell *data, int *new_pipe, \
									int *prev_pipe_read_fd)
{
	if (data->pipe_index != data->pipe_count)
		safe_close(data, &new_pipe[WRITE]);
	if (data->pipe_index != 0)
		safe_close(data, prev_pipe_read_fd);
}

/**
 * Cleanup function for when forking has failed. Closes open file descriptors,
 * calls wait_for_children and performs a clean exit.
 *
 * @param data				Pointer to main data struct
 * @param new_pipe			Pointer to int[2] that contains pipe fds
 * @param prev_pipe_read_fd	File descriptor value of previously created pipe's
 *							read end, -1 if previous pipe doesn't exist
 * @see wait_for_children
 * @see clean_error_exit
 */
static void	handle_fork_failure(t_minishell *data, int *new_pipe, \
						int prev_pipe_read_fd)
{
	safe_close(data, &prev_pipe_read_fd);
	safe_close(data, &new_pipe[READ]);
	wait_for_children(data);
	clean_error_exit(data, MSG_ERROR_FORK, ERROR_FORK);
}
