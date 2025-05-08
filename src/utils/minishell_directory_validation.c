/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_directory_validation.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:07:40 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 15:49:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if it is possible to open a file descriptor to a file with name str
 * using the O_DIRECTORY flag. Returns true on success, false on failure.
 *
 * @param data	Pointer to main data struct
 * @param str	String with file name
 *
 * @return	true if str is a directory, false if not
 */
bool	is_a_directory(t_minishell *data, const char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		safe_close(data, &fd);
		return (true);
	}
	return (false);
}

/**
 * Checks if the file that has name str has '/' as its last character and has
 * type file.
 *
 * @param data	Pointer to main data struct
 * @param str	String with file name
 *
 * @return	true if str ends with '/', thus pretending to be a directory, false
 *			if not
 */
bool	pretends_to_be_a_directory(t_minishell *data, const char *str)
{
	if (!str)
		return (false);
	if (str[ft_strlen(str) - 1] != '/')
		return (false);
	if (is_a_directory(data, str))
		return (false);
	return (true);
}
