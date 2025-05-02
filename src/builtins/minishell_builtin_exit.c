/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:57:46 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/29 15:20:20 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper Function to validate arguments
 * returns error if too many arguments or non numeric arguments
 *
 * @param data	main data struct
 * @param token	token reference
 */
static int	validate_arguments(t_token *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	if (!ft_isnumstr(token->value))
		return (EXIT_BLTN_NAN);
	else if (is_argument(token->next))
		return (EXIT_BLTN_TOOMANY);
	return (EXIT_SUCCESS);
}

/**
 * Function to call EXIT builtin
 *
 * @param data	main data struct
 * @param builtin_token	builtin_token reference
 */
int	builtin_exit(t_minishell *data)
{
	t_token	*token;

	token = copy_cmd_and_args_within_pipe(data);
	if (data->pipe_count == 0)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!token->next)
		clean_exit(data, EXIT_SUCCESS);
	if (validate_arguments(token->next) == EXIT_BLTN_NAN)
	{
		ft_putstr_fd(STR_PROMPTSTART "exit: ", STDERR_FILENO);
		ft_putstr_fd(token->next->value, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		clean_exit(data, EXIT_BLTN_NAN);
	}
	else if (validate_arguments(token->next) == EXIT_BLTN_TOOMANY)
	{
		ft_putendl_fd(STR_PROMPTSTART "exit: too many arguments",
				STDERR_FILENO);
		data->last_rval = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (ft_isnumstr(token->next->value))
		clean_exit(data, ft_atoi(token->value));
	return (EXIT_SUCCESS);
}
