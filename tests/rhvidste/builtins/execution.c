/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:57:28 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:08:17 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to set paths for execution
 *
 * @param command	command input
 * @param mypaths	list of paths
 */
char	*set_paths(char *command, char **mypaths)
{
	bool	it_works;
	char	*fullpath;
	char	*onepath;
	int		i;

	i = 0;
	it_works = false;
	while (mypaths[i])
	{
		onepath = ft_strjoin(mypaths[i], "/");
		fullpath = ft_strjoin(onepath, command);
		free(onepath);
		if (access(fullpath, F_OK) == 0)
		{
			it_works = true;
			break ;
		}
		else
			free(fullpath);
		i++;
	}	
	free_array(mypaths);
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
char	*path_parsing(char *command, char **envp)
{
	char	**mypaths;
	char	*fullpath;
	int		i;

	if (command[0] == '.' && command[1] == '/')
	{
//		printf("COMMAND IS BINARY!!\n");
		fullpath = ft_strdup(command);
		return (fullpath);
	}
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	mypaths = ft_split(envp[i] + 5, ':');
	i = 0;
	fullpath = set_paths(command, mypaths);
	return (fullpath);
}

/**
 * Function that runs execve / execution
 *
 * @param argv	argument input vector
 * @param envp	envp_arr (not list)
 */
void	cmd_exec(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	path = path_parsing(command[0], envp);
	if (!path)
	{
		free_array(command);
		exit(1);
	}
	if (execve(path, command, envp) == -1)
	{
		printf("execve failed");
		free_array(command);
		free(path);
	}
	perror("execve failed");
	free_array(command);
	free(path);
}

// Function to run executibal from path.
/**
 * Function to run exicutable from path
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
int	run_prog(char *input, char **envp)
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
		cmd_exec(input, envp);
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
