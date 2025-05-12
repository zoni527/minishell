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
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	validate_raw_input(t_minishell *data)
{
	bool	error;

	error = false;
	if (ft_is_whitespace_string(data->raw_input))
		error = true;
	else if (ft_strlen(data->raw_input) > ARG_MAX)
	{
		error = true;
		handle_error(data, NULL, ERROR_TOOLONG);
	}
	else if (has_unclosed_quotes(data->raw_input))
	{
		error = true;
		handle_error(data, data->raw_input, ERROR_UNCLOSED);
	}
	if (error)
	{
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
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	validate_tokens(t_minishell *data)
{
	if (contains_syntax_error(data->token_list))
	{
		log_syntax_error(syntax_error_at_token(data->token_list));
		data->last_rval = EXIT_SYNTAXERROR;
		free((void *)data->raw_input);
		reset_data(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
