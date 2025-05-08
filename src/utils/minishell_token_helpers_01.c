/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_helpers_01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:56:50 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 13:00:30 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a new list of tokens from within the pipe specified by
 * data->pipe_index.
 * 
 * @param data	Pointer to main data struct
 *
 * @return	Copy of tokens within the pipe specified by data->pipe_index
 */
t_token	*copy_tokens_within_pipe(const t_minishell *data)
{
	const t_token	*start;
	t_token			*tokens;
	t_token			*new;

	start = skip_to_current_pipe(data);
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
 * Creates a new list of tokens from within the pipe specified by
 * data->pipe_index, selects only command and argument tokens.
 *
 * @param data	Pointer to main data struct
 *
 * @return	Copy of command and argument tokens within the pipe specified by
 *			data->pipe_index
 */
t_token	*copy_cmd_and_args_within_pipe(const t_minishell *data)
{
	const t_token	*start;
	t_token			*tokens;
	t_token			*new;

	start = skip_to_current_pipe(data);
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
 * Creates a new list of tokens from within the pipe specified by
 * data->pipe_index, selects only tokens related to redirections
 * (input, output, heredoc, append, file names and delimiters).
 * 
 * @param data	Pointer to main data struct
 *
 * @return	Copy of redirection tokens within the pipe specified by
 *			data->pipe_index
 */
t_token	*copy_redirections_within_pipe(const t_minishell *data)
{
	const t_token	*start;
	t_token			*tokens;
	t_token			*new;

	start = skip_to_current_pipe(data);
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		if (is_redirection(start) || is_heredoc(start))
		{
			new = copy_token(data, start);
			append_token(&tokens, new);
			new->index = start->index;
			new = copy_token(data, start->next);
			append_token(&tokens, new);
			new->index = start->next->index;
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
 *
 * @return	Deep copy of token
 */
t_token	*copy_token(const t_minishell *data, const t_token *token)
{
	t_token	*new;

	new = ft_ma_calloc(data->arena, 1, sizeof(t_token));
	new->value = ft_ma_strdup(data->arena, token->value);
	new->index = token->index;
	new->type = token->type;
	return (new);
}
