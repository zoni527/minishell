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

/**
 * Skips to token that when evaluated by function f returns true. Returns NULL
 * if such a token can't be found.
 *
 * @param list	First node in list of tokens
 * @param f		Pointer to a token classification function
 *
 * @return	First token in list that returns true when evaluated by function f,
 *			NULL if such a token isn't found
 */
t_token	*skip_to(const t_token *list, bool (*f)(const t_token *token))
{
	while (list && !f(list))
		list = list->next;
	return ((t_token *)list);
}

/**
 * If list points to a token that when called by f returns true, skip that
 * token and skip to the next token of that type.
 *
 * @param list	First node in list of tokens
 * @param f		Pointer to a token classification function
 *
 * @return	Next token in list that returns true when evaluated by function f
 *			(can't be the first token), NULL if such a token isn't found
 *
 * @see skip_to
 */
t_token	*skip_to_next(const t_token *list, bool (*f)(const t_token *token))
{
	if (!list)
		return (NULL);
	if (f(list))
		list = list->next;
	return (skip_to(list, f));
}

/**
 * Returns token to the first non pipe token within the pipe that is specified
 * by data->pipe_index.
 *
 * @param data	Pointer to main data struct
 *
 * @return	First token inside the pipe determined by data->pipe_index
 *
 * @see skip_to
 */
t_token	*skip_to_current_pipe(const t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

	pipe_index = data->pipe_index;
	token = data->token_list;
	while (pipe_index)
	{
		token = skip_to(token, is_pipe);
		token = token->next;
		--pipe_index;
	}
	return (token);
}

/**
 * Checks whether list contains a token that returns true when evaluated by
 * function f.
 *
 * @param list	First node in list of tokens
 * @param f		Pointer to a token classification function
 *
 * @return	True if list contains token that returns true when evaluated by
 *			function f, false if not
 *
 * @see skip_to
 */
bool	tokens_contain(const t_token *list, bool (*f)(const t_token *token))
{
	list = skip_to(list, f);
	if (list)
		return (true);
	return (false);
}

/**
 * Cheks if the pipe specified by data->pipe_index contains a token that
 * returns true when evaluated by function f.
 *
 * @param data	Pointer to main data struct
 * @param f		Pointer to a token classification function
 *
 * @return	True if pipe contains a token that returns true when evaluated by
 *			function f, false if not
 *
 * @see skip_to_current_pipe
 * @see skip_to
 */
bool	pipe_has(const t_minishell *data, bool (*f)(const t_token *token))
{
	t_token	*token;

	token = skip_to_current_pipe(data);
	while (token && !is_pipe(token))
	{
		if (f(token))
			return (true);
		token = token->next;
	}
	return (false);
}
