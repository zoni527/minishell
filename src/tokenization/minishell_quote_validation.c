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
