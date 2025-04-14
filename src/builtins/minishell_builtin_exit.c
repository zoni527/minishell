/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:46 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/14 11:51:44 by rhvidste         ###   ########.fr       */
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

void	builtin_exit(t_minishell *data, t_token *builtin_token)
{
	t_token	*token;

	token = builtin_token;
	token = proccess_token(data, token);
	if (data->pipe_count > 0)
	{
		data->last_rval = EXIT_SUCCESS;
		exit(0);
	}
	if (token == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		return ;
	}
	else
	{
		data->last_rval = ft_atoi(token->value);
		return ;
	}
}
