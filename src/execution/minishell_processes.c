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

// Function to run executibal from path.
/**
 * Function to run exicutable from path
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
int	run_prog(t_minishell *data, const char *input, char **envp)
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

int		child_process_pipe(t_minishell *data, char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
//		ft_error();
	pid = fork();
	if (pid == -1)
		return (1);
//		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (1);
//			ft_error();
		close(fd[1]);
		cmd_exec(data, argv, envp);
		perror("execve failed");
		return (1);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (1);
//			ft_error();
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	handle_infile(t_minishell *data, char *path)
{
	data->fd_in = open(path, O_RDONLY);
	if (data->fd_in < 0)
		return (1);
	return (0);
}

int	handle_outfile(t_minishell *data, char *path)
{
	data->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out < 0)
		return (1);
	return (0);
}

static void	read_to_here_doc(t_minishell *data, int *fd, const char *limiter)
{
	while (1)
	{
		close(fd[0]);
		data->here_doc_input = readline("> ");
		if (ft_strncmp(limiter, data->here_doc_input, ft_strlen(limiter)) == 0)			{
//			write(fd[1], data->here_doc_input, ft_strlen(here_doc_input))
			free((void *)data->here_doc_input);
//			exit(1);
			break ;
		}
		write(fd[1], data->here_doc_input, ft_strlen(data->here_doc_input));
		add_history(data->here_doc_input);
		free((void *)data->here_doc_input);
	}
	close(fd[1]);
}

int	here_doc(t_minishell *data, const char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	reader = fork();
	if (reader == 0)
	{
		read_to_here_doc(data, fd, limiter);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);

	}
	return (0);
}

