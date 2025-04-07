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
		onepath = NULL;
		if (access(fullpath, F_OK) == 0)
		{
			it_works = true;
			break ;
		}
		else
			fullpath = NULL;
		i++;
	}	
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

	if (ft_strncmp(command, "./", 2) == 0 || (command[0] == '/'))
	{
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
void	cmd_exec(t_minishell *data, char **command, char **envp)
{
	char	*path;

	ft_putendl_fd("inside of cmd exe\n", 2);
	path = path_parsing(data, command[0], envp);
	ft_putendl_fd("path passing complete:", 2);
	ft_putendl_fd(path, 2);
	if (!path)
	{
		exit(1);
	}
	if (execve(path, command, envp) == -1)
	{
		printf("execve failed");
	}
}
