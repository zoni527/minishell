/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_is_token_01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:42:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 18:43:46 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(t_token *token)
{
	if (!token)
		return (false);
	return (token->type >= PIPE && token->type <= APPEND);
}

bool	is_pipe(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == PIPE)
		return (true);
	return (false);
}

bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == REDIRECT_OUTPUT || token->type == REDIRECT_INPUT \
		|| token->type == APPEND)
		return (true);
	return (false);
}

bool	is_input_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == REDIRECT_INPUT)
		return (true);
	return (false);
}

bool	is_output_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == REDIRECT_OUTPUT)
		return (true);
	return (false);
}
