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

/**
 * Checks if token->type is an operator type.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_operator(const t_token *token)
{
	if (!token)
		return (false);
	return (token->type >= PIPE && token->type <= APPEND);
}

/**
 * Checks if token->type is PIPE.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_pipe(const t_token *token)
{
	if (token && token->type == PIPE)
		return (true);
	return (false);
}

/**
 * Checks if token->type matches input or ouptut redirection or appending.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_redirection(const t_token *token)
{
	if (!token)
		return (false);
	if (token->type == REDIRECT_OUTPUT || token->type == REDIRECT_INPUT \
		|| token->type == APPEND)
		return (true);
	return (false);
}

/**
 * Checks if token->type is REDIRECT_INPUT.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_input_redirection(const t_token *token)
{
	if (token && token->type == REDIRECT_INPUT)
		return (true);
	return (false);
}

/**
 * Checks if token->type is REDIRECT_OUTPUT
 *
 * @param token	Pointer to token which is checked
 */
bool	is_output_redirection(const t_token *token)
{
	if (token && token->type == REDIRECT_OUTPUT)
		return (true);
	return (false);
}
