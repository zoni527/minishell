/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quote_toggling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:53:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/14 10:57:31 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to temporarily subtitute quotes with invalid characters to treat
 * them as regular characters.
 *
 * @param str	String to deactivate quotes from
 */
char	*deactivate_quotes(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str[i] = -1;
		if (str[i] == '"')
			str[i] = -2;
		++i;
	}
	return (str);
}

/**
 * Function to reactivate previously deactivated quotes.
 *
 * @param str	String to reactivate quotes from
 */
char	*reactivate_quotes(char *str)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = '\'';
		if (str[i] == -2)
			str[i] = '"';
		++i;
	}
	return (str);
}
