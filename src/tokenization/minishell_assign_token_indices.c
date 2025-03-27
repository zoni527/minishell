/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_assign_token_indices.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:54:59 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 18:55:36 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_indices(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	if (!token)
		return ;
	token->index = 0;
	token = token->next;
	while (token)
	{
		token->index = token->prev->index + 1;
		token = token->next;
	}
}
