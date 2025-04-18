/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_variable_expansion_02.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:06:54 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 16:07:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a t_var node with the correct values to perform expansion for $?.
 * Basically this function uses a modified version of itoa to assign
 * data->last_rval to variable->value.
 *
 * @param data	Pointer to main data struct
 */
t_var	*question_mark_variable(t_minishell *data)
{
	t_var	*variable;
	int		str_len;
	int		last_rval;

	variable = ft_ma_calloc(data->arena, 1, sizeof(t_var));
	variable->key = "?";
	last_rval = (unsigned char)data->last_rval;
	str_len = ft_int_digits(last_rval);
	variable->value = ft_ma_calloc(data->arena, str_len + 1, sizeof(char));
	while (--str_len)
	{
		variable->value[str_len] = (last_rval % 10) + '0';
		last_rval /= 10;
	}
	variable->value[0] = (last_rval % 10) + '0';
	return (variable);
}
