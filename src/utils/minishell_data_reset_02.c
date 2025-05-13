/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data_reset_02.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:48:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/21 16:48:10 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Appends variable var to environment variable list.
 *
 * @param env_list	Pointer to first element in environment variable list
 * @param var		Node to be appended
 */
void	append_var(t_var **env_list, t_var *var)
{
	t_var	*end;

	if (!env_list || !var)
		return ;
	if (!*env_list)
	{
		*env_list = var;
		return ;
	}
	end = *env_list;
	while (end->next)
		end = end->next;
	end->next = var;
	var->prev = end;
}

/**
 * Copies environment variable list into given memarena.
 *
 * @param arena		Memarena to copy into
 * @param env_list	Linked list of environment variables
 *
 * @return	First node in copied environment list
 */
t_var	*copy_env_to_memarena(t_minishell *data, const t_var *env_list)
{
	t_var	*copy;
	t_var	*new_env;

	new_env = NULL;
	while (env_list)
	{
		copy = ms_calloc(data, 1, sizeof(t_var));
		copy->raw = ms_strdup(data, env_list->raw);
		copy->key = ms_strdup(data, env_list->key);
		copy->value = ms_strdup(data, env_list->value);
		append_var(&new_env, copy);
		env_list = env_list->next;
	}
	return (new_env);
}
