/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:16:42 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/10 16:17:52 by rhvidste         ###   ########.fr       */
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
		ft_putendl_fd(" ", 1);
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
 * Helper function to print token to fd
 * or add a new line if at the last argument
 *
 * @param builtin_token	root builtin token reference
 */
static int	print_token(t_token *token)
{
	if (token->type == ARGUMENT)
	{
		ft_putstr_fd(token->value, 1);
		if (token->next && token->next->type == ARGUMENT)
			ft_putstr_fd(" ", 1);
	}
	if (token->next == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (1);
}

/**
 * Function to execute ECHO
 * builtin function
 *
 * @param data	main data struct
 * @param builtin_token	root builtin token reference
 */
void	builtin_echo(t_minishell *data, t_token *builtin_token)
{
	t_token	*token;

	token = builtin_token;
	token = proccess_token(data, token);
	if (token == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		return ;
	}
	while (token)
	{
		if (print_token(token) == 0)
			break ;
		token = token->next;
	}
	data->last_rval = EXIT_SUCCESS;
}
