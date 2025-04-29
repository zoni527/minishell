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
 */
int	change_dir(t_minishell *data, char *str)
{
	if (chdir(str) == -1)
	{
		handle_error(data, str, ERROR_CHDIR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
