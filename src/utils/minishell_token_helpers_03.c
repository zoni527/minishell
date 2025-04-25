/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_helpers_03.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:56:30 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 12:57:41 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param data	Pointer to main data struct
 * @see	pipe_has
 */
bool	pipe_has_redirections(const t_minishell *data)
{
	return (pipe_has(data, is_redirection));
}

/**
 * @param data	Pointer to main data struct
 * @see	pipe_has
 */
bool	pipe_has_heredoc(const t_minishell *data)
{
	return (pipe_has(data, is_heredoc));
}

/**
 * @param data	Pointer to main data struct
 * @see	pipe_has
 */
bool	pipe_has_input_redirection(const t_minishell *data)
{
	return (pipe_has(data, is_input_redirection));
}

/**
 * @param data	Pointer to main data struct
 * @see	pipe_has
 */
bool	pipe_has_output_redirection(const t_minishell *data)
{
	return (pipe_has(data, is_output_redirection));
}

/**
 * @param data	Pointer to main data struct
 * @see	pipe_has
 */
bool	pipe_has_append(const t_minishell *data)
{
	return (pipe_has(data, is_append));
}
