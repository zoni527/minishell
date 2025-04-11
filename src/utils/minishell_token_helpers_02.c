/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_helpers_02.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:38:02 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/11 11:50:33 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*skip_to_pipe_by_index(const t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

	pipe_index = data->pipe_index;
	token = data->token_list;
	while (pipe_index)
	{
		while (!is_pipe(token))
			token = token->next;
		token = token->next;
		--pipe_index;
	}
	return (token);
}
