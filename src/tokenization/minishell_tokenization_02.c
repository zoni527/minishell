/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenization_02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:42:24 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/20 18:02:42 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Creates new token node using str, uses memory arena to request heap memory.
 * <p>
 * Does an initial categorization for operators, everything else will be a word
 * at first. More granular categorization will follow after all possible
 * expansions, word splits and quote removals are completed.
 *
 * @param arena	Pointer to first node in memarena
 * @param str	String is assigned to be the value of the new token node
 * @return		Return newly created token node
 */
t_token	*new_token_node(t_memarena *arena, const char *str)
{
	t_token	*new;

	new = ft_ma_calloc(arena, 1, sizeof(t_token));
	new->value = (char *)str;
	if (*str == '|')
		new->type = PIPE;
	else if (ft_strncmp(str, "<", 2) == 0)
		new->type = REDIRECT_INPUT;
	else if (ft_strncmp(str, ">", 2) == 0)
		new->type = REDIRECT_OUTPUT;
	else if (ft_strncmp(str, "<<", 3) == 0)
		new->type = HEREDOC;
	else if (ft_strncmp(str, ">>", 3) == 0)
		new->type = APPEND;
	else
		new->type = WORD;
	return (new);
}

/**
 * Adds a given token node to the end of given list of tokens.
 *
 * @param list	Pointer to token pointer that is the first node in the list
 * @param token	Pointer to token node that will be added to the end of the list
 */
void	append_token(t_token **list, t_token *token)
{
	t_token	*end;

	if (!list || !token)
		return ;
	if (!*list)
	{
		*list = token;
		return ;
	}
	end = *list;
	while (end->next)
		end = end->next;
	end->next = token;
	if (token)
	{
		token->prev = end;
		token->id = end->id + 1;
	}
}

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

/**
 * Inserts node "new" to be the prev node of node "current".
 *
 * @param current	Pointer to selected token node
 * @param new		Pointer to instertable token node
 */
void	insert_token_left(t_token *current, t_token *new)
{
	t_token	*prev;

	if (!current || !new)
		return ;
	prev = current->prev;
	if (prev)
		prev->next = new;
	current->prev = new;
	new->next = current;
	new->prev = prev;
}
