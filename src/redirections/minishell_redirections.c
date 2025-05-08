/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:59:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 13:27:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(t_minishell *data, const t_token *token);

/**
 * Handler function for managing redirections and heredocs within a pipe.
 *
 * @param data	Pointer to main data struct
 *
 * @return	EXIT_SUCCESS if redirections succeed, EXIT_FAILURE if not
 */
int	handle_redirections(t_minishell *data)
{
	t_token	*redirection_tokens;

	if (!pipe_has_redirections(data) && !pipe_has_heredoc(data))
		return (EXIT_SUCCESS);
	redirection_tokens = copy_redirections_within_pipe(data);
	while (redirection_tokens)
	{
		if (redirect(data, redirection_tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirection_tokens = redirection_tokens->next->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * Handler function for managing redirections and heredocs within a pipe.
 *
 * @param data	Pointer to main data struct
 * @param token	Token to match a redirection type against
 *
 * @return	EXIT_SUCCESS if redirections succeed, EXIT_FAILURE if not
 */
static int	redirect(t_minishell *data, const t_token *token)
{
	if (is_input_redirection(token))
	{
		if (redirect_input(data, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_output_redirection(token))
	{
		if (redirect_output(data, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_append(token))
	{
		if (redirect_append(data, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_heredoc(token))
	{
		if (redirect_heredoc(data, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
