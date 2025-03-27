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

t_bltn_type	get_builtin_type(t_token *token)
{
	if (!token || token->type != BUILTIN)
		return (-1);
	if (ft_strncmp(token->value, "echo", ft_strlen("echo") + 1) == 0)
		return (BLTN_ECHO);
	if (ft_strncmp(token->value, "cd", ft_strlen("cd") + 1) == 0)
		return (BLTN_CD);
	if (ft_strncmp(token->value, "pwd", ft_strlen("pwd") + 1) == 0)
		return (BLTN_PWD);
	if (ft_strncmp(token->value, "export", ft_strlen("export") + 1) == 0)
		return (BLTN_EXPORT);
	if (ft_strncmp(token->value, "unset", ft_strlen("unset") + 1) == 0)
		return (BLTN_UNSET);
	if (ft_strncmp(token->value, "env", ft_strlen("env") + 1) == 0)
		return (BLTN_ENV);
	if (ft_strncmp(token->value, "exit", ft_strlen("exit") + 1) == 0)
		return (BLTN_EXIT);
	return (-1);
}

const char	*get_token_type_str(t_token *token)
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
		type_str = "unknown";
	return (type_str);
}

t_token	*get_token_by_index(t_token *list, int index)
{
	while (list)
	{
		if ((int)list->index == index)
			return (list);
		list = list->next;
	}
	return (NULL);
}
