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

bool	is_append(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == APPEND)
		return (true);
	return (false);
}

bool	is_heredoc(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == HEREDOC)
		return (true);
	return (false);
}

bool	is_builtin(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == BUILTIN)
		return (true);
	if ((!token->prev || is_pipe(token->prev)) \
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
