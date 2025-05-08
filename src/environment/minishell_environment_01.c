/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:52:15 by rhvidste          #+#    #+#             */
/*   Updated: 2025/05/08 11:19:06 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to get specific envp variable from the list
 * and return it in a variable
 *
 * @param key	key name of target envp variable
 * @param envp	pointer to first envp element
 *
 * @return	Value of matched environment variable, NULL if not found
 */
char	*ms_getenv(t_minishell *data, char *key)
{
	t_var	*current;
	char	*value;

	if (!key || !data->minishell_env)
		return (NULL);
	current = data->minishell_env;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			value = ft_ma_strdup(data->arena, current->value);
			return (value);
		}
		else
			current = current->next;
	}
	return (NULL);
}

/**
 * Helper Function to fnd and replace a envp variable
 * from within export builtin
 *
 * @param data	pointer to main data struct
 * @param key	key input
 * @param value	value input
 * @param raw	raw input
 *
 * @return	NULL when matching variable is found, last element in list if not
 */
static t_var	*find_and_replace_env(t_minishell *data,
					char *key,
					char *value,
					char *raw)
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
 *
 * @param name	key input
 * @param value	value input
 * @param envp	enviroment pointer
 */
void	ms_setenv(t_minishell *data, char *key, char *value)
{
	char	*raw;
	t_var	*last;

	last = NULL;
	raw = ft_ma_strjoin(data->arena, key, "=");
	if (value != NULL)
		raw = ft_ma_strjoin(data->arena, raw, value);
	last = find_and_replace_env(data, key, value, raw);
	if (last)
	{
		last->next = create_new_env_var(data,
				ft_ma_strdup(data->arena, raw),
				ft_ma_strdup(data->arena, key),
				ft_ma_strdup(data->arena, value));
		last->next->prev = last;
	}
	else if (last == NULL && data->minishell_env == NULL)
		data->minishell_env = create_new_env_var(data,
				ft_ma_strdup(data->arena, raw),
				ft_ma_strdup(data->arena, key),
				ft_ma_strdup(data->arena, value));
}

/**
 * Function to remove an envp variable
 *
 * @param name	key input
 * @param envp	enviroment pointer
 */
void	remove_env(t_minishell *data, char *key)
{
	t_var	*current;

	current = data->minishell_env;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (current->next == NULL)
			{
				if (current->prev)
					current->prev->next = NULL;
				else
					data->minishell_env = NULL;
				return ;
			}
			current->next->prev = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			else
				data->minishell_env = current->next;
			return ;
		}
		current = current->next;
	}
}
