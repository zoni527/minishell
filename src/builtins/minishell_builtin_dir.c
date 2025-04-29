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
 */
int	get_current_dir(t_minishell *data)
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
		data->last_rval = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	data->last_rval = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

/**
 * Function to switch dir
 *
 * @param str	dir address to change to
 */
int	change_dir(t_minishell *data, char *str)
{
	char	*error;

	if (chdir(str) == -1)
	{
		error = ft_ma_strjoin(data->arena, "minishell: cd: ", str);
		perror(error);
		data->last_rval = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	data->last_rval = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

/**
 * Safe Function to call getcwd amd handle case
 * where it returns NULL
 *
 * @param data	pointer to the main data struct
 */
char	*safe_getcwd(t_minishell *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = ft_calloc(1, sizeof(char));
		if (!cwd)
			clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	}
	return (cwd);
}
