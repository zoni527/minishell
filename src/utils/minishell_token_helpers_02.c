/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_helpers_02.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:38:02 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/11 11:50:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*skip_to_pipe_by_index(const t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

	pipe_index = data->pipe_index;
	token = data->token_list;
	while (pipe_index)
	{
		while (!is_pipe(token))
			token = token->next;
		token = token->next;
		--pipe_index;
	}
	return (token);
}

bool	tokens_contain(const t_token *list, bool (*f)(const t_token *token))
{
	while (list && !f(list))
		list = list->next;
	if (list)
		return (true);
	return (false);
}

bool	pipe_has(const t_minishell *data, bool (*f)(const t_token *token))
{
	t_token	*token;

	token = skip_to_pipe_by_index(data);
	while (token && !is_pipe(token))
	{
		if (f(token))
			return (true);
		token = token->next;
	}
	return (false);
}

t_token	*skip_to_next(const t_token *list, bool (*f)(const t_token *token))
{
	if (!list)
		return (NULL);
	if (f(list))
		list = list->next;
	while (list && !f(list))
		list = list->next;
	return ((t_token *)list);
}
