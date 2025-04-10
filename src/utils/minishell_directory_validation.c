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

bool	is_a_directory(t_minishell *data, const char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		try_to_close_fd(data, &fd);
		return (true);
	}
	return (false);
}

bool	pretends_to_be_a_directory(t_minishell *data, const char *str)
{
	int	fd;

	if (!str)
		return (false);
	if (str[ft_strlen(str) - 1] != '/')
		return (false);
	if (is_a_directory(data, str))
		return (false);
	return (true);
}
