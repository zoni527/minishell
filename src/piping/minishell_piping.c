/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:32:51 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/03 15:51:05 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_minishell *data);
static void	close_pipe_fds_in_parent(t_minishell *data, int *new_pipe, \
									int *prev_pipe_read_fd);
static void	wait_for_children(t_minishell *data);
static void	create_new_pipe_and_assign_fds(t_minishell *data, int *new_pipe, \
									int prev_pipe_read_fd);

void	handle_fork_failure(t_minishell *data, int *new_pipe, \
						int prev_pipe_read_fd)
{
	if (prev_pipe_read_fd != -1)
		close(prev_pipe_read_fd);
	if (new_pipe[READ] > 2)
		close(new_pipe[READ]);
	wait_for_children(data);
	clean_error_exit(data, MSG_ERROR_FORK, ERROR_FORK);
}

void	piping(t_minishell *data)
{
	int		new_pipe[2];
	pid_t	pid;
	int		prev_pipe_read_fd;

	data->pipe_count = 2;
	data->pipe_index = 0;
	pid = 1;
	prev_pipe_read_fd = -1;
	while (data->pipe_index <= data->pipe_count && pid != 0)
	{
		create_new_pipe_and_assign_fds(data, new_pipe, prev_pipe_read_fd);
		pid = fork();
		if (pid < 0)
			handle_fork_failure(data, new_pipe, prev_pipe_read_fd);
		else if (pid == 0)
			break ;
		else if (pid != 0)
			close_pipe_fds_in_parent(data, new_pipe, &prev_pipe_read_fd);
		prev_pipe_read_fd = new_pipe[READ];
		data->pipe_index++;
	}
	if (pid == 0)
		child_process(data);
	else
		wait_for_children(data);
}

static void	create_new_pipe_and_assign_fds(t_minishell *data, int *new_pipe, \
									int prev_pipe_read_fd)
{
	if (data->pipe_index != data->pipe_count)
		try_to_pipe(data, new_pipe);
	if (prev_pipe_read_fd != -1)
		data->pipe_fds[READ] = prev_pipe_read_fd;
	if (data->pipe_index != data->pipe_count)
		data->pipe_fds[WRITE] = new_pipe[WRITE];
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! Catch exit values later !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static void	wait_for_children(t_minishell *data)
{
	size_t	children;
	pid_t	pid;

	children = data->pipe_index + 1;
	while (children--)
		pid = wait(NULL);
}

static void	close_pipe_fds_in_parent(t_minishell *data, int *new_pipe, \
									int *prev_pipe_read_fd)
{
	if (data->pipe_index != data->pipe_count)
		try_to_close_fd(data, &new_pipe[WRITE]);
	if (data->pipe_index != 0)
		try_to_close_fd(data, prev_pipe_read_fd);
}

bool	pipe_has_redirections(t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

	if (!data || !data->token_list)
		return (false);
	pipe_index = data->pipe_index;
	token = data->token_list;
	while (pipe_index)
	{
		while (token->type != PIPE)
			token = token->next;
		token = token->next;
		--pipe_index;
	}
	while (token && token->type != PIPE)
	{
		if (is_redirection(token))
			return (true);
		token = token->next;
	}
	return (false);
}

void	handle_redirections(t_minishell *data)
{
	(void)data;
}

static void	child_process(t_minishell *data)
{
	char	**argv;

	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
	if (pipe_has_redirections(data))
		handle_redirections(data);
	if (data->pipe_index == 0)
	{
		char	*argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
	else if (data->pipe_index == 1)
	{
		char	*argv[] = {"cat", NULL};
		execve("/usr/bin/cat", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
	else
	{
		char	*argv[] = {"wc", NULL};
		execve("/usr/bin/wc", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
}
