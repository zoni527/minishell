/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:37:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/11 14:55:20 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to call the ENV builtin
 *
 * @param data	pointer to the main data struct
 */
void	builtin_env(t_minishell *data)
{
	t_var	*var;

	var = data->minishell_env;
	while (var)
	{
		if (ft_strchr(var->raw, '='))
		{
			ft_putendl_fd(var->raw, 1);
		}
		var = var->next;
	}
	data->last_rval = 0;
}
