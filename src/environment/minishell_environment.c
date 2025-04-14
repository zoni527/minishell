/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:52:15 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/09 12:12:14 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to parse the envp into
 * a linked list for later use
 *
 * @param data	Main data struct
 * @param envp	system envp input
 */
void	env_list_from_envp(t_minishell *data, char **envp)
{
	t_var	*current;
	char	*vals[3];
	int		i;
	int		j;

	current = NULL;
	i = -1;
	while (envp[++i])
	{
		vals[0] = ft_ma_strdup(data->arena, envp[i]);
		j = ft_char_index(vals[0], '=');
		vals[1] = ft_ma_substr(data->arena, vals[0], 0, j);
		vals[2] = ft_ma_substr(data->arena, vals[0], \
						(j + 1), ft_strlen(vals[0]) - (j + 1));
		if (current == NULL)
		{
			current = create_new_env_var(data, vals[0], vals[1], vals[2]);
			data->minishell_env = current;
			continue ;
		}
		current->next = create_new_env_var(data, vals[0], vals[1], vals[2]);
		current->next->prev = current;
		current = current->next;
	}
}

/**
 * Function to convert envp_list to an NULL terminated
 * array of strings
 *
 * @param envp	pointer to first envp element
 */
char	**create_envp_arr_from_custom_env(t_minishell *data, t_var *envp_list)
{
	t_var	*head;
	t_var	*current;
	char	**envp_arr;
	int		list_len;
	int		i;

	i = -1;
	list_len = 0;
	head = NULL;
	current = NULL;
	list_len = get_env_list_size(envp_list);
	envp_arr = ft_ma_malloc(data->arena, (sizeof(char *) * (list_len + 1)));
	head = envp_list;
	current = head;
	while (++i < list_len)
	{
		envp_arr[i] = current->raw;
		current = current->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

/**
 * Function to get specific envp variable from the list
 * and return it in a variable
 *
 * @param name	name of target envp variable
 * @param envp	pointer to first envp element
 */
char	*ms_getenv(t_minishell *data, const char *name, t_var *envp)
{
	t_var	*current;
	char	*sub_name;

	if (!name || !envp)
		return (NULL);
	current = NULL;
	if (ft_strncmp(name, "getenv", 6) == 0)
		sub_name = ft_ma_substr(data->arena, name, 7, ft_strlen(name) - 6);
	else
		sub_name = ft_ma_strdup(data->arena, name);
	if (!sub_name)
		return (NULL);
	current = envp;
	while (current)
	{
		if (ft_strncmp(sub_name, current->key, ft_strlen(sub_name)) == 0)
		{
			sub_name = ft_ma_strdup(data->arena, current->value);
			return (sub_name);
		}
		else
			current = current->next;
	}
	return (NULL);
}

/**
 * Function to set or create a envp variable
 *
 * @param name	key input
 * @param value	value input
 * @param envp	enviroment pointer
 */
int	ms_setenv(t_minishell *data, char *key, char *value, t_var *envp)
{
	char	*raw;
	t_var	*current;
	t_var	*last;

	raw = ft_ma_strjoin(data->arena, key, "=");
	raw = ft_ma_strjoin(data->arena, raw, value);
	current = envp;
	while (current)
	{
		if (strncmp(key, current->key, ft_strlen(key)) == 0)
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

/**
 * Function to remove an envp variable
 *
 * @param name	key input
 * @param envp	enviroment pointer
 */
int	remove_env(char *key, t_var *envp)
{
	t_var	*current;

	current = NULL;
	current = envp;
	while (current)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0)
		{
			if (current->next == NULL)
			{
				current->prev->next = NULL;
				return (0);
			}
			current->next->prev = current->prev;
			current->prev->next = current->next;
			return (0);
		}
		current = current->next;
	}
	return (0);
}
