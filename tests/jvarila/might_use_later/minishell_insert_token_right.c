/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_insert_token_right.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:04:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 15:05:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Inserts node "new" to be the next node of node "current".
 *
 * @param current	Pointer to selected token node
 * @param new		Pointer to instertable token node
 */
void	insert_token_right(t_token *current, t_token *new)
{
	t_token	*next;

	if (!current || !new)
		return ;
	next = current->next;
	if (next)
		next->prev = new;
	current->next = new;
	new->prev = current;
	new->next = next;
}
