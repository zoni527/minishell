/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:30:03 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 11:51:49 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that creates a null terminated argv to pass to execve
 *
 * @param data	main data struct
 * @param command	token for the relevant command
 */
char	**create_args_arr(t_minishell *data, t_token *command)
{
	char	**args;
	t_token	*token;
	int		count;
	int		i;

	token = command;
	count = 1;
	while (token->next && token->next->type == ARGUMENT)
	{
		count++;
		token = token->next;
	}
	args = ft_ma_malloc(data->arena, sizeof(char *) * (count + 1));
	i = -1;
	token = command;
	while (++i < count)
	{
		args[i] = ft_ma_strdup(data->arena, token->value);
		token = token->next;
	}
	args[count] = NULL;
	return (args);
}

/**
 * Function to set paths for execution
 *
 * @param command	command input
 * @param mypaths	list of paths
 */
static char	*set_paths(t_minishell *data, const char *command, char **mypaths)
{
	char	*fullpath;
	char	*onepath;
	int		i;

	i = 0;
	while (mypaths[i])
	{
		onepath = ft_ma_strjoin(data->arena, mypaths[i], "/");
		fullpath = ft_ma_strjoin(data->arena, onepath, command);
		if (access(fullpath, F_OK) == 0)
		{
			return (fullpath);
		}
		else
			fullpath = NULL;
		i++;
	}
	return (NULL);
}

/**
 * Function that parses the paths for cmd execution
 *
 * @param command	command input
 * @param envp	envp_arr input (not list)
 */
static char	*path_parsing(t_minishell *data, const char *command, char **envp)
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

/*
 * Function that runs execve / execution
 *
 * @param argv	argument input vector
 * @param envp	envp_arr (not list)
 */
void	cmd_exec(t_minishell *data, char **command, char **envp)
{
	char	*path;

	path = path_parsing(data, command[0], envp);
	if (!path)
	{
		handle_error(data, command[0], ERROR_NOSUCH);
		return ;
	}
	execve(path, command, envp);
	if (errno == ENOENT)
	{
		data->last_rval = EXIT_NOSUCH;
		data->error = ERROR_NOCMD;
	}
	else if (errno == EACCES)
	{
		data->last_rval = EXIT_PERMISSION;
		data->error = ERROR_PERMISSION;
	}
	else
	{
		data->last_rval = EXIT_FAILURE;
		data->error = 1;
	}
	handle_error(data, command[0], ERROR_EXECVE);
}
