/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_classification.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:52:16 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 18:52:22 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Loops through tokens and assigns categories to them based on position
 * and the surrounding tokens.
 *
 * @param data	Pointer to main data struct
 */
void	token_classification(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		if (is_operator(token))
			;
		else if (!token->prev || is_pipe(token->prev))
		{
			if (is_builtin(token))
				token->type = BUILTIN;
			else
				token->type = COMMAND;
		}
		else if (token->prev && is_redirection(token->prev))
			token->type = FILE_NAME;
		else
			token->type = ARGUMENT;
		token = token->next;
	}
}

t_bltn_type	return_builtin_type(t_token *token)
{
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
