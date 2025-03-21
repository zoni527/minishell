/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:08:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:11:47 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to print the current directory path
 * PWD
 *
 * @param void	no input
 */
int	get_current_dir(void)
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
int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}

