/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_dir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:52:16 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/25 15:07:58 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to print the current directory path
 * PWD
 *
 * @param void	no input
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	get_current_dir(t_minishell *data)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		handle_error(data, NULL, ERROR_GETCWD);
		return (EXIT_FAILURE);
	}
	ft_putendl(buffer);
	free (buffer);
	return (EXIT_SUCCESS);
}

/**
 * Function to switch dir
 *
 * @param str	dir address to change to
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	change_dir(t_minishell *data, char *str)
{
	if (access(str, F_OK) < 0)
	{
		handle_error(data, ms_strjoin(data, "cd: ", str),
			ERROR_NOSUCH);
		return (EXIT_FAILURE);
	}
	else if (access(str, X_OK) < 0)
	{
		handle_error(data, ms_strjoin(data, "cd: ", str),
			ERROR_PERMISSION);
		return (EXIT_FAILURE);
	}
	if (chdir(str) == -1)
	{
		handle_error(data, ms_strjoin(data, "cd: ", str),
			ERROR_CHDIR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Safe Function to call getcwd amd handle case
 * where it returns NULL
 *
 * @param data	pointer to the main data struct
 *
 * @return	String inside memory arena, can't be NULL
 */
char	*safe_getcwd(t_minishell *data)
{
	char	*cwd;
	char	*temp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = ft_calloc(1, sizeof(char));
		if (!cwd)
			clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	}
	temp = cwd;
	cwd = ms_strdup(data, cwd);
	free(temp);
	return (cwd);
}
