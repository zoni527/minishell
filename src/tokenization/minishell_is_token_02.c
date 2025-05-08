/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_is_token_02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:44:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 16:58:26 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if token->type is APPEND.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is FILE_NAME, false if not
 */
bool	is_append(const t_token *token)
{
	if (token && token->type == APPEND)
		return (true);
	return (false);
}

/**
 * Checks if token->type is HEREDOC.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is HEREDOC, false if not
 */
bool	is_heredoc(const t_token *token)
{
	if (token && token->type == HEREDOC)
		return (true);
	return (false);
}

/**
 * Checks if token is a builtin or command, based on its position in relation
 * to other tokens, or the previously assigned type.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is BUILTIN or COMMND, otherwise check if token
 *			hasn't been categorized yet (type is WORD), and if not check if
 *			it qualifies to be a command or builtin (first token or only
 *			redirections and or a pipe to the left), return false if not
 */
bool	is_builtin_or_command(const t_token *token)
{
	if (!token)
		return (false);
	if (token->type == BUILTIN || token->type == COMMAND)
		return (true);
	if (!is_word(token))
		return (false);
	token = token->prev;
	if (!token || is_pipe(token))
		return (true);
	while (token && (is_file_name(token) || is_delimiter(token)))
		token = token->prev->prev;
	if (!token || is_pipe(token))
		return (true);
	return (false);
}

/**
 * Checks if token is a builtin based on its position in relation to other
 * tokens in combination with the the token->value, or the previously
 * assigned type.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token position and name match the requirements of being a
 *			builtin, false if not
 *
 * @see is_builtin_or_command
 */
bool	is_builtin(const t_token *token)
{
	if (!token)
		return (false);
	if (token->type == BUILTIN)
		return (true);
	if (!is_word(token))
		return (false);
	if (is_builtin_or_command(token)
		&& (ft_strcmp(token->value, "echo") == 0
			|| ft_strcmp(token->value, "cd") == 0
			|| ft_strcmp(token->value, "pwd") == 0
			|| ft_strcmp(token->value, "export") == 0
			|| ft_strcmp(token->value, "unset") == 0
			|| ft_strcmp(token->value, "env") == 0
			|| ft_strcmp(token->value, "exit") == 0))
		return (true);
	return (false);
}

/**
 * Checks if token is a command based on its already assigned type or if
 * it is at the right position in relation to other tokens to be a command,
 * and that it isn't a builtin.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is COMMAND or if the token fulfills the
 *			requirements of being categorized as a command, false if not
 *
 * @see is_builtin_or_command
 * @see is_builtin
 */
bool	is_command(const t_token *token)
{
	if (!token)
		return (false);
	if (token->type == COMMAND)
		return (true);
	if (is_builtin_or_command(token) && !is_builtin(token))
		return (true);
	return (false);
}
