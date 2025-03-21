/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:16:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:18:57 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function that returns the length of a list
 *
 * @param begin_list	pointer to the beginning of the list
 */
int	get_list_size(t_var *begin_list)
{
	if (begin_list == 0)
		return (0);
	else
		return (1 + get_list_size(begin_list->next));
}

/**
 * Function that frees the enviroment list
 *
 * @param head	pointer to the head of the list
 */
void	free_list(t_var *head)
{
	while(head)
	{
		t_var *temp = head;
		free(temp->raw);
		free(temp->key);
		free(temp->value);
		head = head->next;
		free(temp);
	}
}

/**
 * Function that prints env from
 * linked list
 *
 * @param list	list to print contents of
 */
void	print_env_list(t_var *list)
{
	t_var *current = list;
	while (current)
	{
		printf("%s\n", current->raw);
		current = current->next;
	}
}

/**
 * Function appends node and adds values
 * variable it finds.
 *
 * @param data	Main data struct
 * @param raw	Raw input
 * @param key	Key input
 * @param value	Value input
 */
t_var	*append_node(t_var *prev, char *raw, char *key, char *value)
{
	t_var *new_node = (t_var *)malloc(sizeof(t_var));
	new_node->raw = raw;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = prev;
	return (new_node);
}
