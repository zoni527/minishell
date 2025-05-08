/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntax_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:42:43 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/08 14:37:54 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if token list contains tokens that would be categorized as a syntax
 * error, such as a pipe as the first token, two redirection operators next to
 * each other or nothing after a pipe.
 *
 * @param list	First node in list of tokens
 *
 * @return	true if list contains syntax error, false if not
 */
bool	contains_syntax_error(t_token *list)
{
	if (!list)
		return (false);
	if (list->type == PIPE)
		return (true);
	while (list)
	{
		if (is_pipe(list) && is_pipe(list->next))
			return (true);
		else if ((is_redirection(list) || is_heredoc(list))
			&& is_operator(list->next))
			return (true);
		else if (is_pipe(list) && !list->next)
			return (true);
		list = list->next;
	}
	return (false);
}

/**
 * Function to retrieve token at which syntax error occurs.
 *
 * @param list	First node in list of tokens
 *
 * @return	Token at which syntax error occurs, NULL if token can't be found
 */
t_token	*syntax_error_at_token(t_token *list)
{
	if (!list)
		return (NULL);
	if (list->type == PIPE)
		return (list);
	while (list)
	{
		if (is_pipe(list) && is_pipe(list->next))
			return (list->next);
		else if ((is_redirection(list) || is_heredoc(list))
			&& is_operator(list->next))
			return (list->next);
		list = list->next;
	}
	return (NULL);
}
