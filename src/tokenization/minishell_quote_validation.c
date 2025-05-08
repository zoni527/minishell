/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quote_validation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:47:03 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 17:02:26 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks whether str contains unclosed quotes by attempting to skip to a
 * closing quote when a quote is found. If a closing quote can't be found it
 * means that the string contains an unclosed quote.
 *
 * @param str	String to be searched
 *
 * @return	true if string contains unclosed quotes, false if not
 */
bool	has_unclosed_quotes(const char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str != '\'' && *str != '"')
		{
			str++;
			continue ;
		}
		str = ft_strchr(str + 1, *str);
		if (!str)
			return (true);
		else
			str++;
	}
	return (false);
}
