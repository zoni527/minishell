/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_processes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:02 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/26 11:03:59 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
#include <unistd.h>

// Function to run executibal from path.
/**
 * Function to run exicutable from path
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
int	run_prog(t_minishell *data, char **input, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}

	if (pid == 0)
	{
//		char	*argv[] = {
//				"nvim",
//				"test.txt",
//				NULL
//		};
//
//		execve("/home/rhvidste/.local/bin/nvim-linux-x86_64/bin/nvim", argv, envp);
//		token = get_next_pipe_token(token);
//		if (token->next->type == PIPE)
//		{
//			dup2(data.pipe[1], STDOUT_FILENO)
//		}
//		close (data,pipe[0]);
//
		cmd_exec(data, input, envp);
		perror("execve failed");
		exit(1);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
	return (0);
}

int		child_process_pipe(t_minishell *data, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	printf("ENTER\n");
	if (pipe(fd) == -1)
	{
		perror("Pipe failure");
		return (1);
//		ft_error();
	}
	pid = fork();
	printf("process forked\n");
	if (pid == -1)
	{
		printf("PID FAILED\n");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
//		ft_error();
	if (pid == 0)
	{

		printf("CHILD PROCCESS ENTERED\n");
		close(fd[0]); //close read end, child only writes.
		if (data->fd_out == 0)
		{
			ft_putendl_fd ("fd_out = 0", 2);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				ft_putendl_fd("dup2 failed", 2);
				close(fd[1]);
				exit(1);
			}
		}
		else
		{
			ft_putendl_fd("fd_out = fd_out", 2);
			if (dup2(fd[1], data->fd_out) == -1)
			{
				ft_putendl_fd("dup2 failed", 2);
				close(fd[1]);
				exit (1);
			}
		}
//		close(fd[1]);
//		printf("going to execution\n");
		ft_putendl_fd("going to execution", 2);
		cmd_exec(data, argv, envp);
//		perror("execve failed");
//		return (1);
	}
	else
	{
		printf("PARENT PROCESS ENTERED\n");
		close(fd[1]);
		if (data->fd_in == 0)
		{
			printf("fd_in = 0\n");
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				printf("dup2 failed\n");
				return (1);
			}
		}
		else
		{
			printf("fd_in = fd_in\n");
			if (dup2(fd[0], data->fd_in) == -1)
			{
				printf("dup2 failed\n");
				return (1);
//				ft_error();
			}
		}
//		close(fd[0]);
		printf("entering waitpid\n");
//		waitpid(pid, &status, 0);
		if(waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid failed\n");
			return (1);
		}
		close(fd[0]);
		printf("waitpid successfull\n");
		printf("EXIT\n");
	}
	return (0);
}

int	handle_infile(t_minishell *data, char *path)
{
	data->fd_in = open(path, O_RDONLY);
	data->std_in = 	dup(STDIN_FILENO);
	if (data->fd_in == -1)
	{
		perror ("Error opening infile");
		data->fd_in = 0;
	}
	if (data->fd_in < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (data->fd_in > 0 && dup2(data->fd_in, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (data->fd_in > 0)
	{
//		ft_putstr_fd("minishell : fd > 0, closing fd_in\n", STDERR_FILENO);
		close(data->fd_in);
	}

//	printf("DATA->FD_IN: %d\n", data->fd_in);
	return (0);
}

int	handle_outfile(t_minishell *data, char *path)
{
	data->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (1);
	}
	if (data->fd_out > 0 && dup2(data->fd_out, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (data->fd_out > 0)
		close (data->fd_out);
	return (0);
}

