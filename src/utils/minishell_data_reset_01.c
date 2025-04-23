/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data_reset_01.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:29:28 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/21 16:59:40 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*copy_env(const t_var *env);
static t_var	*copy_var(const t_var *var);
static void		free_env(t_var **env);
static void		free_var_contents(t_var *var);

/**
 * Temporarily copies minishell's environment to a heap location outside of the
 * memarena, resets the memarena and then copies the environment back into it.
 * Frees the temporary environment afterwards, and sets pointers in data that
 * were previously pointing to addresses inside the memarena to NULL.
 *
 * @param data	Pointer to main data struct
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	reset_arena_and_pointers(t_minishell *data)
{
	t_var	*env_copy;

	if (!data->minishell_env)
	{
		ft_reset_memarena(data->arena);
		return (EXIT_SUCCESS);
	}
	env_copy = copy_env(data->minishell_env);
	if (!env_copy)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	ft_reset_memarena(data->arena);
	data->minishell_env = copy_env_to_memarena(data->arena, env_copy);
	free_env(&env_copy);
	data->token_list = NULL;
	data->hd_delimiters = NULL;
	data->hd_file_names = NULL;
	return (EXIT_SUCCESS);
}

/**
 * Creates a deep copy of a t_var in a new location on the heap.
 *
 * @param var	Environment variable to be copied
 * @return	Deep copy of var, prev and next assigned to NULL
 */
static t_var	*copy_var(const t_var *var)
{
	t_var	*copy;

	copy = ft_calloc(1, sizeof(t_var));
	if (!copy)
		return (NULL);
	copy->raw = ft_strdup(var->raw);
	copy->key = ft_strdup(var->key);
	copy->value = ft_strdup(var->value);
	if (!copy->raw && !copy->key && !copy->value)
	{
		free(copy->raw);
		free(copy->key);
		free(copy->value);
		free(copy);
		return (NULL);
	}
	return (copy);
}

/**
 * Frees the raw, key and value fields in var and sets the pointers to NULL.
 *
 * @param var	Environment variable whose fields to free
 */
static void	free_var_contents(t_var *var)
{
	if (!var)
		return ;
	free(var->raw);
	free(var->key);
	free(var->value);
	var->raw = NULL;
	var->key = NULL;
	var->value = NULL;
}

/**
 * Frees all nodes in environment variable linked list. Sets the linked list
 * pointer to NULL after freeing.
 *
 * @param env	Pointer to first node in environment list
 */
static void	free_env(t_var **env)
{
	t_var	*temp;

	if (!env || !*env)
		return ;
	temp = *env;
	while (temp->next)
	{
		temp = temp->next;
		free_var_contents(temp->prev);
		free(temp->prev);
	}
	free_var_contents(temp);
	free(temp);
	*env = NULL;
}

/**
 * Returns a copy of environment variable linked list, placed on the heap but
 * outside the memarena.
 *
 * @param env	First node in environment list
 */
static t_var	*copy_env(const t_var *env)
{
	t_var	*copy;
	t_var	*temp;

	copy = NULL;
	while (env)
	{
		temp = copy_var(env);
		if (!temp)
		{
			free_env(&copy);
			return (NULL);
		}
		append_var(&copy, temp);
		env = env->next;
	}
	return (copy);
}
