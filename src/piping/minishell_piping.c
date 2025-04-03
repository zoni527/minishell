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

#include "libft.h"
#include "minishell.h"

static void chain_of_pipes(t_minishell *data, char *envp[]);

void	piping(t_minishell *data, char *envp[])
{
	//data->pipe_count = count_pipes(data->token_list);
	//if (data->pipe_count <= 0)
	//	return ;
	if (pipe(data->pipe_fds))
		exit(ERROR_PIPE);
	chain_of_pipes(data, envp);
}

static void chain_of_pipes(t_minishell *data, char *envp[])
{
	pid_t	pid;
	size_t	index;

	index = 0;
	pid = fork();
	if (pid < 0)
		exit(ERROR_FORK);
	if (pid != 0)
	{
		if (waitpid(pid, NULL, 0) < 0)
			ft_putendl_fd("waitpid fail, 1", 2);
		return ;
	}
	while (index < 2 && pid == 0)
	{
		pid = fork();
		if (pid < 0)
			exit(ERROR_FORK);
		// When process already has a child
		if (pid != 0)
			break ;
		index++;
	}
	if (index != 0)
	{
		if (dup2(data->pipe_fds[READ], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit (ERROR_DUP2);
		}
	}
	if (index != 2)
	{
		if (dup2(data->pipe_fds[WRITE], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit (ERROR_DUP2);
		}
	}
	if (close(data->pipe_fds[READ]))
	{
		ft_putendl_fd("close fail, 1", 2);
		exit(ERROR_CLOSE);
	}
	if (close(data->pipe_fds[WRITE]))
	{
		ft_putendl_fd("close fail, 2", 2);
		exit(ERROR_CLOSE);
	}
	ft_free_memarena(data->arena);
	if (index == 0)
	{
		char *argv[] = {"yes", NULL};
		execve("/usr/bin/yes", argv, envp);
		ft_putendl_fd("After execve, fuck", 2);
	}
	else if (index == 1)
	{
		char *argv[] = {"head", NULL};
		execve("/usr/bin/head", argv, envp);
		ft_putendl_fd("After execve, fuck", 2);
	}
	else
	{
		char *argv[] = {"cat", NULL};
		execve("/usr/bin/cat", argv, envp);
		ft_putendl_fd("After execve, fuck", 2);
	}
	ft_putendl_fd("Waiting for a child", 2);
	if (pid != 0)
	{
		if (waitpid(pid, NULL, 0) < 0)
			ft_putendl_fd("waitpid fail, 2", 2);
	}
}
