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
 * Returns true if there is a redirection token within the pipe specified by
 * data->pipe_index, false if not.
 *
 * @param data	Pointer to main data struct
 */
bool	pipe_has_redirections(const t_minishell *data)
{
	return (pipe_has(data, is_redirection));
}

bool	pipe_has_heredoc(const t_minishell *data)
{
	return (pipe_has(data, is_heredoc));
}
