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

/**
 * Helper Function to validate arguments
 * returns error if too many arguments
 *
 * @param data	main data struct
 * @param token	token reference
 */
static int	validate_arguments(t_minishell *data, t_token *token)
{
	if (data->pipe_count == 0)
	{
		if (!token)
		{
			data->last_rval = 0;
			return (EXIT_SUCCESS);
		}
		if (token->next)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			data->last_rval = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * Helper Function to handle if there are
 * non numerical characters
 *
 * @param data	main data struct
 * @param token	token reference
 */
static void	num_handler(t_minishell *data, t_token *token)
{
	char	*error;

	if (ft_isnumstr(token->value))
	{
		data->last_rval = ft_atoi(token->value);
		ft_putendl_fd("exit", STDERR_FILENO);
		return ;
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		error = ft_ma_strjoin(data->arena, "minishell: exit: ", token->value);
		error = ft_ma_strjoin(data->arena, error, \
						": numeric argument required");
		ft_putendl_fd(error, STDERR_FILENO);
		data->last_rval = EXIT_BLTN_NAN;
		return ;
	}
}

/**
 * Function to call EXIT builtin
 *
 * @param data	main data struct
 * @param builtin_token	builtin_token reference
 */
int	builtin_exit(t_minishell *data, t_token *builtin_token)
{
	t_token	*token;

	token = builtin_token;
	token = proccess_token(data, token);
	if (validate_arguments(data, token) == EXIT_FAILURE)
		return (EXIT_BLTN_NO_EXIT);
	if (token == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		ft_putendl_fd("exit", STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
	else
	{
		num_handler(data, token);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
