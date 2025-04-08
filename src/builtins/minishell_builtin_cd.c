/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:32:42 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 14:00:59 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to print the current directory path
 * PWD
 *
 * @param void	no input
 */
static int	get_current_dir(void)
{
	char	*buffer = getcwd(NULL, 0); // Dynamically allocate memory
	
	if (buffer != NULL)
	{
		printf("%s\n", buffer);
		free (buffer);
	}
	else
	{
		perror("getcwd error");
		return (1);
	}
	return (0);
}

/**
 * Function to switch dir
 *
 * @param str	dir address to change to
 */
static int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}

/**
 * Function to call the CD builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	builtin_cd(t_minishell *data, char *input, t_var *envp)
{
	char	*path;
	char	*old_path;
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	old_path = getcwd(NULL, 0); // get current path to set as old path before change.
	ms_setenv(data, "OLDPWD", old_path, envp);//set the OLD pwd enviroment variable
	path = ft_ma_substr(data->arena, input, 3, (ft_strlen(input) - 2));
	if (path[0] == '~')
	{
		new_path = ft_ma_substr(data->arena, path, 1, (ft_strlen(path) - 1));
		home_path = ms_getenv(data, "HOME", envp);
		new_home_path = ft_ma_strjoin(data->arena, home_path, new_path);
		change_dir(new_home_path);
		ms_setenv(data, "PWD", new_home_path, envp);
	}
	//Here we check is CD is just added on its own.
	else if (path[0] == '\0')
	{
		home_path = getenv("HOME");
		ms_setenv(data, "PWD", home_path, envp);
		change_dir(home_path);
	}
	else
	{
		change_dir(path);
		new_path = getcwd(NULL, 0);
		ms_setenv(data, "PWD", new_path, envp);
	}
}
