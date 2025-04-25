/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_export.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:56:14 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/24 15:11:28 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to set or create a envp variable
 * from within export builtin
 *
 * @param data	pointer to main data struct
 * @param key	key input
 * @param value	value input
 * @param raw	raw input
 */
int	ms_setenv_export(t_minishell *data, char *key, char *value, char *raw)
{
	t_var	*current;
	t_var	*last;

	current = data->minishell_env;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			current->raw = raw;
			current->value = value;
			return (0);
		}
		last = current;
		current = current->next;
	}
	if (last)
	{
		last->next = create_new_env_var(data, raw, key, value);
		last->next->prev = last;
	}
	return (0);
}
