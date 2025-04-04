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

static void	chain_of_pipes(t_minishell *data, char *envp[]);

void	clean_exit(t_minishell *data, int exit_code)
{
	if (data->pipe_fds[READ] >= 0)
		close(data->pipe_fds[READ]);
	if (data->pipe_fds[WRITE] >= 0)
		close(data->pipe_fds[WRITE]);
	free((void *)data->raw_input);
	ft_free_memarena(data->arena);
	exit(exit_code);
}

void	try_to_close_fd(t_minishell *data, int *fd)
{
	if (fd < 0)
		return ;
	if (close(*fd) < 0)
	{
		ft_putendl_fd(MSG_ERROR_CLOSE, STDERR_FILENO);
		clean_exit(data, ERROR_CLOSE);
	}
	*fd = -1;
}

void	try_to_dup2(t_minishell *data, int fd1, int fd2)
{
	if (fd1 < 0 || fd2 < 0)
		return ;
	if (dup2(fd1, fd2) < 0)
	{
		ft_putendl_fd(MSG_ERROR_DUP2, STDERR_FILENO);
		clean_exit(data, ERROR_DUP2);
	}
}

void	redirect_stdout(t_minishell *data)
{
	try_to_dup2(data, data->pipe_fds[WRITE], STDOUT_FILENO);
	try_to_close_fd(data, &data->pipe_fds[WRITE]);
}

void	redirect_stdin(t_minishell *data)
{
	try_to_dup2(data, data->pipe_fds[READ], STDIN_FILENO);
	try_to_close_fd(data, &data->pipe_fds[READ]);
}

void	piping(t_minishell *data, char *envp[])
{
	int		new_pipe[2];
	size_t	index;
	pid_t	pid;
	int		prev_pipe_read_fd;
	//data->pipe_count = count_pipes(data->token_list);
	//if (data->pipe_count <= 0)
	//	return ;

	data->pipe_count = 2;
	index = 0;
	pid = 1;
	prev_pipe_read_fd = -1;
	while (index <= data->pipe_count && pid != 0)
	{
		if (index != data->pipe_count)
		{
			if (pipe(new_pipe) < 0)
				exit(ERROR_PIPE);
			ft_putendl_fd("Pipe created", STDERR_FILENO);
		}
		if (prev_pipe_read_fd != -1)
			data->pipe_fds[READ] = prev_pipe_read_fd;
		if (index != data->pipe_count)
			data->pipe_fds[WRITE] = new_pipe[WRITE];
		data->pipe_index = index;
		pid = fork();
		if (pid != 0)
		{
			if (index != data->pipe_count)
				try_to_close_fd(data, &new_pipe[WRITE]);
			if (index != 0)
				try_to_close_fd(data, &prev_pipe_read_fd);
		}
		prev_pipe_read_fd = new_pipe[READ];
		index++;
	}
	if (pid == 0)
		chain_of_pipes(data, envp);
	else
	{
		int i = data->pipe_count + 1;
		while (i--)
			wait(NULL);
	}
}

bool	pipe_has_redirections(t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

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

static void chain_of_pipes(t_minishell *data, char *envp[])
{
	if (data->pipe_index != 0)
		redirect_stdin(data);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout(data);
	if (pipe_has_redirections(data))
		handle_redirections(data);
	if (data->pipe_index == 0)
	{
		char *argv[] = {"ls", NULL};
		ft_putendl_fd("Made it above execve in first command, wish me luck", 2);
		execve("/usr/bin/ls", argv, envp);
		ft_putstr_fd("You have made it past execve, you shouldn't be here", STDERR_FILENO);
	}
	else if (data->pipe_index == 1)
	{
		char *argv[] = {"cat", NULL};
		ft_putendl_fd("Made it above execve in second command, wish me luck", 2);
		execve("/usr/bin/cat", argv, envp);
		ft_putstr_fd("You have made it past execve, you shouldn't be here", STDERR_FILENO);
	}
	else
	{
		char *argv[] = {"wc", NULL};
		ft_putendl_fd("Made it above execve in third command, wish me luck", 2);
		execve("/usr/bin/wc", argv, envp);
		ft_putstr_fd("You have made it past execve, you shouldn't be here", STDERR_FILENO);
	}
}
