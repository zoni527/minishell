/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:58:45 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 16:50:38 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that returns the length of a list
 *
 * @param begin_list	pointer to the beginning of the list
 */
int	get_env_list_size(t_var *begin)
{
	if (begin == 0)
		return (0);
	else
		return (1 + get_env_list_size(begin->next));
}

/**
 * Function that prints env from
 * linked list
 *
 * @param list	list to print contents of
 */
void	print_custom_env(t_var *list)
{
	t_var	*current;

	current = list;
	while (current)
	{
		ft_putendl_fd(current->raw, 1);
		current = current->next;
	}
}

/**
 * Function creates and returns an 
 * env node
 *
 * @param data	Main data struct
 * @param raw	Raw input
 * @param key	Key input
 * @param value	Value input
 */
t_var	*create_new_env_var(t_minishell *data,
		char *raw, char *key, char *value)
{
	t_var	*new_node;

	new_node = ft_ma_malloc(data->arena, sizeof(t_var));
	new_node->raw = raw;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}
