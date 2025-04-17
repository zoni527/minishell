/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_helpers_01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:56:50 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/11 10:33:01 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a new list of tokens from the tokens starting at start, stops when
 * the list ends or another pipe is found.
 * 
 * @param data	Pointer to main data struct
 * @param start	First token within pipe
 */
t_token	*copy_tokens_within_pipe(t_minishell *data, const t_token *start)
{
	t_token	*tokens;
	t_token	*new;

	if (is_pipe(start))
		start = start->next;
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		new = copy_token(data, start);
		append_token(&tokens, new);
		start = start->next;
	}
	return (tokens);
}

/**
 * Creates a new list of tokens from the tokens starting at start, selects only
 * commands, builtins and arguments, so it skips redirections and heredocs.
 * 
 * @param data	Pointer to main data struct
 * @param start	First token within pipe
 */
t_token	*copy_cmd_and_args_within_pipe(t_minishell *data, const t_token *start)
{
	t_token	*tokens;
	t_token	*new;

	if (is_pipe(start))
		start = start->next;
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		if (is_builtin_or_command(start) || is_argument(start))
		{
			new = copy_token(data, start);
			append_token(&tokens, new);
		}
		start = start->next;
	}
	return (tokens);
}

/**
 * Creates a new list of tokens from the tokens starting at start, selects only
 * redirections and file names.
 * 
 * @param data	Pointer to main data struct
 * @param start	First token within pipe
 */
t_token	*copy_redirections_within_pipe(t_minishell *data, const t_token *start)
{
	t_token	*tokens;
	t_token	*new;

	if (is_pipe(start))
		start = start->next;
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		if (is_redirection(start))
		{
			new = copy_token(data, start);
			append_token(&tokens, new);
			new = copy_token(data, start->next);
			append_token(&tokens, new);
			start = start->next;
		}
		start = start->next;
	}
	return (tokens);
}

/**
 * Creates a new list of tokens from the tokens starting at start, selects only
 * heredocs and delimiters.
 * 
 * @param data	Pointer to main data struct
 * @param start	First token within pipe
 */
t_token	*copy_heredocs_within_pipe(t_minishell *data, const t_token *start)
{
	t_token	*tokens;
	t_token	*new;

	if (is_pipe(start))
		start = start->next;
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		if (is_heredoc(start))
		{
			new = copy_token(data, start);
			append_token(&tokens, new);
			new = copy_token(data, start->next);
			append_token(&tokens, new);
			start = start->next;
		}
		start = start->next;
	}
	return (tokens);
}

/**
 * Creates and returns a deep copy of an existing token. Doesn't assign next
 * and prev.
 * 
 * @param data	Pointer to main data struct
 * @param start	Token to copy
 */
t_token	*copy_token(t_minishell *data, const t_token *token)
{
	t_token	*new;

	new = ft_ma_calloc(data->arena, 1, sizeof(t_token));
	new->value = ft_ma_strdup(data->arena, token->value);
	new->index = token->index;
	new->type = token->type;
	return (new);
}
