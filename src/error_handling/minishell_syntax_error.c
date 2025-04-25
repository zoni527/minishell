/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntax_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:42:43 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/02 14:42:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		list = list->next;
	}
	return (false);
}

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
