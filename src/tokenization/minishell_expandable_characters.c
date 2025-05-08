/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expandable_characters.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:45 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/07 15:17:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Categorization function for variable name expansion, matches acceptable
 * characters for variable names.
 *
 * @param c	Int to check against
 *
 * @return	true if c is '?', '_' or alphanumeric
 */
bool	is_expandable_char(int c)
{
	if (c == '?' || ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
