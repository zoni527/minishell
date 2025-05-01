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
 * @param builtin_token	token reference
 */
static t_token	*proccess_token(t_token *token)
{
	if (token->next == NULL)
	{
		ft_putendl("");
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
 * Helper function to print token to stdout
 * or add a new line if at the last argument
 *
 * @param token	root builtin token reference
 */
static int	print_token(t_token *token)
{
	if (token->type == ARGUMENT)
	{
		ft_putstr(token->value);
		if (token->next && token->next->type == ARGUMENT)
			ft_putstr(" ");
	}
	if (token->next == NULL)
	{
		ft_putstr("\n");
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * Function to execute ECHO
 * builtin function
 *
 * @param data	main data struct
 */
void	builtin_echo(t_minishell *data)
{
	t_token	*token;

	token = copy_cmd_and_args_within_pipe(data);
	token = proccess_token(token);
	if (token == NULL)
		return ;
	while (token)
	{
		if (print_token(token) == 0)
			break ;
		token = token->next;
	}
	data->last_rval = 0;
}
