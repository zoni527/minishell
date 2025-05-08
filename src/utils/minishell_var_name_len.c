/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_var_name_len.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:35:22 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 11:24:40 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Custom function to get the length of a string that is meant to be used as a
 * variable name, so the characters can be alphanumeric or an underscore.
 *
 * @param str	String containing variable name
 *
 * @return	Length of variable name
 */
size_t	var_name_len(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		++len;
	return (len);
}
