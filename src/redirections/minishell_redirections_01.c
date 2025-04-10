/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections_01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:59:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 16:49:54 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_minishell *data)
{
	return (EXIT_SUCCESS);
}

void	remove_redirections_from_pipe(t_token **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return ;
	token = *tokens;
	if (is_pipe(token))
		token = token->next;
	while (token && !is_pipe(token))
	{
		if (is_redirection(token))
		{
			if (!token->prev)
				*tokens = token->next->next;
			else
				token->prev->next = token->next->next;
			token = token->next;
		}
		token = token->next;
	}
}

void	remove_all_redirections(t_token **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return ;
	token = *tokens;
	while (token)
	{
		if (is_redirection(token))
		{
			if (!token->prev)
				*tokens = token->next->next;
			else
				token->prev->next = token->next->next;
			token = token->next;
		}
		token = token->next;
	}
}
