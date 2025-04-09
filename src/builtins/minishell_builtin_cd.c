/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:11:23 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 17:10:17 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to print the current directory path
 * PWD
 *
 * @param void	no input
 */
int	get_current_dir(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer != NULL)
	{
		ft_putendl_fd(buffer, 1);
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
int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}

/**
 * Function to handle the tilde key case for CD builtin
 *
 * @param data	minishell data struct
 * @param path	path to change dir too.
 * @param envp	pointer to the first element in envp list
 */
static void	handle_tilde(t_minishell *data, char *path, t_var *envp)
{
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	new_path = ft_ma_substr(data->arena, path, 1, (ft_strlen(path) - 1));
	home_path = ms_getenv(data, "HOME", envp);
	new_home_path = ft_ma_strjoin(data->arena, home_path, new_path);
	change_dir(new_home_path);
	ms_setenv(data, "PWD", new_home_path, envp);
}

/**
 * Function to handle the CD case for CD builtin
 *
 * @param data	main data struct
 * @param envp	pointer to first element in envp list
 */
static	void	handle_cd(t_minishell *data, t_var *envp)
{
	char	*home_path;

	home_path = ms_getenv(data, "HOME", envp);
	ms_setenv(data, "PWD", home_path, envp);
	change_dir(home_path);
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

	old_path = getcwd(NULL, 0);
	ms_setenv(data, "OLDPWD", old_path, envp);
	path = ft_ma_substr(data->arena, input, 3, (ft_strlen(input) - 2));
	if (path[0] == '~')
		handle_tilde(data, path, envp);
	else if (path[0] == '\0')
		handle_cd(data, envp);
	else
	{
		change_dir(path);
		new_path = getcwd(NULL, 0);
		ms_setenv(data, "PWD", new_path, envp);
	}
}
