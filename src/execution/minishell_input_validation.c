/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_validation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:22:00 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/24 14:26:28 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees data->raw_input in case of invalid input.
 *
 * @param data	Pointer to main data struct
 * @return	Int flag for success or failure
 */
int	validate_raw_input(const t_minishell *data)
{
	if (has_unclosed_quotes(data->raw_input))
	{
		ft_putstr_fd(STR_PROMPTSTART , STDERR_FILENO);
		ft_putstr_fd(data->raw_input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(MSG_ERROR_UNCLOSED, STDERR_FILENO);
		free((void *)data->raw_input);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Looks for syntax errors in data->token_list. Reports token with error if it
 * finds one and returns EXIT_FAILURE.
 *
 * Frees data->raw_input in case of invalid input.
 *
 * @param data	Pointer to main data struct
 * @return	Int flag for success or failure
 */
int	validate_tokens(t_minishell *data)
{
	if (contains_syntax_error(data->token_list))
	{
		log_syntax_error(syntax_error_at_token(data->token_list));
		free((void *)data->raw_input);
		reset_arena_and_pointers(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
