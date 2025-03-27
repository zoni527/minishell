/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_analysis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:53:52 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 09:56:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_tokens(t_token *list)
{
	size_t	count;

	if (!list)
		return (0);
	count = 0;
	while (list)
	{
		++count;
		list = list->next;
	}
	return (count);
}

size_t	count_pipes(t_token *list)
{
	size_t	pipes;

	if (!list)
		return (0);
	pipes = 0;
	while (list)
	{
		if (list->type == PIPE)
			++pipes;
		list = list->next;
	}
	return (pipes);
}
