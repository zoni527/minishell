/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_analysis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:53:52 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 09:56:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_type(const t_token *list, \
						bool (*f)(const t_token *token));

/**
 * Counts tokens in token list.
 *
 * @param list	First node in list of tokens
 */
size_t	count_tokens(const t_token *list)
{
	size_t	count;

	if (!list)
		return (0);
	count = 0;
	while (list)
	{
		++count;
		list = list->next;
	}
	return (count);
}

/**
 * Counts pipe tokens in token list.
 *
 * @param list	First node in list of tokens
 */
size_t	count_pipes(const t_token *list)
{
	return (count_type(list, is_pipe));
}

/**
 * Counts heredoc tokens in token list.
 *
 * @param list	First node in list of tokens
 */
size_t	count_heredocs(const t_token *list)
{
	return (count_type(list, is_heredoc));
}

static size_t	count_type(const t_token *list, bool (*f)(const t_token *token))
{
	size_t	count;

	if (!list)
		return (0);
	count = 0;
	while (list)
	{
		if (f(list))
			++count;
		list = list->next;
	}
	return (count);
}

/**
 * Counts variables in list of variables.
 *
 * @param list	First node in list of variables
 */
size_t	count_vars(const t_var *list)
{
	size_t	count;

	count = 0;
	while (list)
	{
		++count;
		list = list->next;
	}
	return (count);
}
