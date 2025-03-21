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

void	toggle_quote_flag(char *quote_flag, char c)
{
	if (*quote_flag == 0)
		*quote_flag = c;
	else if (*quote_flag == c)
		*quote_flag = 0;
}
