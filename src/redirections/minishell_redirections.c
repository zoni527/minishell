/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:59:04 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/11 14:17:44 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_minishell *data)
{
	t_token	*start;
	t_token	*redirection_tokens;

	if (!pipe_has_redirections(data))
		return (EXIT_SUCCESS);
	start = skip_to_pipe_by_index(data);
	redirection_tokens = copy_redirections_within_pipe(data, start);
	while (redirection_tokens)
	{
		if (is_input_redirection(redirection_tokens))
		{
			if (redirect_input(data, redirection_tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (redirect_output(data, redirection_tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirection_tokens = redirection_tokens->next->next;
	}
	return (EXIT_SUCCESS);
}
