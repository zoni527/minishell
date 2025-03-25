/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:49:47 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/25 15:26:10 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * Function to set paths for execution
 *
 * @param command	command input
 * @param mypaths	list of paths
 */
char	*set_paths(t_minishell *data, const char *command, char **mypaths)
{
	bool	it_works;
	char	*fullpath;
	char	*onepath;
	int		i;

	i = 0;
	it_works = false;
	while (mypaths[i])
	{
		onepath = ft_ma_strjoin(data->arena, mypaths[i], "/");
		fullpath = ft_ma_strjoin(data->arena, onepath, command);
//		free(onepath);
		onepath = NULL;
		if (access(fullpath, F_OK) == 0)
		{
			it_works = true;
			break ;
		}
		else
			fullpath = NULL;
//			free(fullpath);
		i++;
	}	
//	free_array(mypaths);
	if (it_works)
		return (fullpath);
	return (NULL);
}

/**
 * Function that parses the paths for cmd execution
 *
 * @param command	command input
 * @param envp	envp_arr input (not list)
 */
char	*path_parsing(t_minishell *data, const char *command, char **envp)
{
	char	**mypaths;
	char	*fullpath;
	int		i;

	if (command[0] == '.' && command[1] == '/')
	{
//		printf("COMMAND IS BINARY!!\n");
		fullpath = ft_ma_strdup(data->arena, command);
		return (fullpath);
	}
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	mypaths = ft_ma_split(data->arena, envp[i] + 5, ':');
	i = 0;
	fullpath = set_paths(data, command, mypaths);
	return (fullpath);
}

/**
 * Function that runs execve / execution
 *
 * @param argv	argument input vector
 * @param envp	envp_arr (not list)
 */
void	cmd_exec(t_minishell *data, const char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_ma_split(data->arena, argv, ' ');
	path = path_parsing(data, command[0], envp);
	if (!path)
	{
//		free_array(command);
		exit(1);
	}
	if (execve(path, command, envp) == -1)
	{
		printf("execve failed");
//		free_array(command);
//		free(path);
	}
	perror("execve failed");
//	free_array(command);
	free(path);
}

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

int		child_process(t_minishell *data, char *argv, char **envp)
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

