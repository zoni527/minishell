/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_getters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:19 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 10:21:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type_str_2(const t_token *token);

/**
 * Tries to match token value to a builtin name.
 *
 * @param token	Token to match against
 *
 * @return	Builtin enum type if match is found, -1 if not
 */
t_bltn_type	get_builtin_type(const t_token *token)
{
	if (!token || token->type != BUILTIN)
		return (-1);
	if (ft_strcmp(token->value, "echo") == 0)
		return (BLTN_ECHO);
	if (ft_strcmp(token->value, "cd") == 0)
		return (BLTN_CD);
	if (ft_strcmp(token->value, "pwd") == 0)
		return (BLTN_PWD);
	if (ft_strcmp(token->value, "export") == 0)
		return (BLTN_EXPORT);
	if (ft_strcmp(token->value, "unset") == 0)
		return (BLTN_UNSET);
	if (ft_strcmp(token->value, "env") == 0)
		return (BLTN_ENV);
	if (ft_strcmp(token->value, "exit") == 0)
		return (BLTN_EXIT);
	return (-1);
}

/**
 * Returns string that matches token->type.
 *
 * @param token	Token to match against
 *
 * @return	String representing the type of the token parameter
 */
const char	*get_token_type_str(const t_token *token)
{
	const char	*type_str;

	if (token->type == WORD)
		type_str = "word";
	else if (token->type == COMMAND)
		type_str = "command";
	else if (token->type == ARGUMENT)
		type_str = "argument";
	else if (token->type == BUILTIN)
		type_str = "builtin";
	else if (token->type == FILE_NAME)
		type_str = "file name";
	else if (token->type == PIPE)
		type_str = "pipe";
	else if (token->type == REDIRECT_INPUT)
		type_str = "redirection input";
	else if (token->type == REDIRECT_OUTPUT)
		type_str = "redirection output";
	else if (token->type == HEREDOC)
		type_str = "heredoc";
	else if (token->type == APPEND)
		type_str = "append";
	else
		type_str = get_token_type_str_2(token);
	return (type_str);
}

/**
 * Returns string that matches token->type.
 *
 * @param token	Token to match against
 *
 * @return	String representing the type of the token parameter
 */
static const char	*get_token_type_str_2(const t_token *token)
{
	const char	*type_str;

	type_str = "unknown";
	if (token->type == DELIMITER)
		type_str = "delimiter";
	return (type_str);
}
