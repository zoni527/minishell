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
 * Helper Function to fnd and replace a envp variable
 * from within export builtin
 *
 * @param data	pointer to main data struct
 * @param key	key input
 * @param value	value input
 * @param raw	raw input
 *
 * @return	NULL if it finds variable matching key, last node if not
 */
static t_var	*find_and_replace_env(t_minishell *data, char *key,
							char *value, char *raw)
{
	t_var	*current;
	t_var	*last;

	last = NULL;
	current = data->minishell_env;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			current->raw = raw;
			current->value = value;
			return (NULL);
		}
		last = current;
		current = current->next;
	}
	return (last);
}

/**
 * Function to set or create a envp variable
 * from within export builtin
 *
 * @param data	pointer to main data struct
 * @param key	key input
 * @param value	value input
 * @param raw	raw input
 */
void	ms_setenv_export(t_minishell *data, char *key, char *value, char *raw)
{
	t_var	*last;

	last = find_and_replace_env(data, key, value, raw);
	if (last)
	{
		last->next = create_new_env_var(data,
				ft_ma_strdup(data->arena, raw),
				ft_ma_strdup(data->arena, key),
				ft_ma_strdup(data->arena, value));
		last->next->prev = last;
	}
	else if (!last && data->minishell_env == NULL)
		data->minishell_env = create_new_env_var(data,
				ft_ma_strdup(data->arena, raw),
				ft_ma_strdup(data->arena, key),
				ft_ma_strdup(data->arena, value));
}
