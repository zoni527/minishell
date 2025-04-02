/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_is_token_02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:44:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 18:50:13 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if token->type is APPEND.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_append(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == APPEND)
		return (true);
	return (false);
}

/**
 * Checks if token->type is HEREDOC.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_heredoc(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == HEREDOC)
		return (true);
	return (false);
}

/**
 * Checks if token is a builtin or command, based on its position in relation
 * to other tokens, or the previously assigned type.
 *
 * @param token	Pointer to token which is checked
 */
bool	is_builtin_or_command(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == BUILTIN || token->type == COMMAND)
		return (true);
	token = token->prev;
	if (!token || is_pipe(token))
		return (true);
	while (token && token->type == FILE_NAME)
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
 */
bool	is_builtin(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == BUILTIN)
		return (true);
	if (is_builtin_or_command(token) \
		&& (ft_strncmp(token->value, "echo", ft_strlen("echo") + 1) == 0 \
		|| ft_strncmp(token->value, "cd", ft_strlen("cd") + 1) == 0 \
		|| ft_strncmp(token->value, "pwd", ft_strlen("pwd") + 1) == 0 \
		|| ft_strncmp(token->value, "export", ft_strlen("export") + 1) == 0 \
		|| ft_strncmp(token->value, "unset", ft_strlen("unset") + 1) == 0 \
		|| ft_strncmp(token->value, "env", ft_strlen("env") + 1) == 0 \
		|| ft_strncmp(token->value, "exit", ft_strlen("exit") + 1) == 0))
		return (true);
	return (false);
}
