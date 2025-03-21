/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:24:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/21 10:26:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Toggles quote flag to be equal to the char c if not set (0), if it was
 * already set to c, it toggles the value back to 0.
 *
 * @param quote_flag	Pointer to character that holds the encountered quote
 * @param c				Character that holds either '\'' or '"'
 */
void	toggle_quote_flag(char *quote_flag, char c)
{
	if (!(c == '\'' || c == '"'))
		return ;
	if (*quote_flag == 0)
		*quote_flag = c;
	else if (*quote_flag == c)
		*quote_flag = 0;
}
