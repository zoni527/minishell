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

t_token	*copy_tokens_within_pipe(t_minishell *data, const t_token *start)
{
	t_token	*tokens;
	t_token	*new;

	if (is_pipe(start))
		start = start->next;
	tokens = NULL;
	while (start && !is_pipe(start))
	{
		new = new_token_node(data->arena, start->value);
		append_token(&tokens, new);
		start = start->next;
	}
	return (tokens);
}

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
			new = new_token_node(data->arena, start->value);
			append_token(&tokens, new);
		}
		start = start->next;
	}
	return (tokens);
}

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
			new = new_token_node(data->arena, start->value);
			append_token(&tokens, new);
			new = new_token_node(data->arena, start->next->value);
			append_token(&tokens, new);
			start = start->next;
		}
		start = start->next;
	}
	return (tokens);
}

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
			new = new_token_node(data->arena, start->value);
			append_token(&tokens, new);
			new = new_token_node(data->arena, start->next->value);
			append_token(&tokens, new);
			start = start->next;
		}
		start = start->next;
	}
	return (tokens);
}
