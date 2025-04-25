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
		else if (is_builtin_or_command(token))
		{
			if (is_builtin(token))
				token->type = BUILTIN;
			else
				token->type = COMMAND;
		}
		else if (token->prev && is_redirection(token->prev))
			token->type = FILE_NAME;
		else if (token->prev && is_heredoc(token->prev))
			token->type = DELIMITER;
		else
			token->type = ARGUMENT;
		token = token->next;
	}
}

t_bltn_type	return_builtin_type(t_token *token)
{
	if (ft_strcmp(token->value, "echo") == 0)
		return(BLTN_ECHO);
	if (ft_strcmp(token->value, "cd") == 0)
		return(BLTN_CD);
	if (ft_strcmp(token->value, "pwd") == 0)
		return(BLTN_PWD);
	if (ft_strcmp(token->value, "export") == 0)
		return(BLTN_EXPORT);
	if (ft_strcmp(token->value, "unset") == 0)
		return(BLTN_UNSET);
	if (ft_strcmp(token->value, "env") == 0)
		return(BLTN_ENV);
	if (ft_strcmp(token->value, "exit") == 0)
		return (BLTN_EXIT);
	return (-1);
}
