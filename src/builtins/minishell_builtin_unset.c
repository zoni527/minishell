/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:55:52 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/11 15:19:51 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper Function to prepare root token
 * before handing to the main function.
 *
 * @param data	main data struct
 * @param builtin_token	token reference
 */
static t_token	*proccess_token(t_minishell *data, t_token *token)
{
	if (token->next == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		return (NULL);
	}
	else
	{
		token = token->next;
		return (token);
	}
	return (NULL);
}

/**
 * Function to call the UNSET builtin
 *
 * @param data	pointer to the main data struct
 * @param builtin_token	pointer to root builtin token
 * @param envp	pointer to fist element in envp array
 */
void	builtin_unset(t_minishell *data, t_token *builtin_token)
{
	t_token	*token;

	token = builtin_token;
	token = proccess_token(data, token);
	if (token == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		return ;
	}
	remove_env(token->value, data->minishell_env);
	data->last_rval = EXIT_SUCCESS;
}
