/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_debug.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:04:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 10:17:00 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints out detailed information about individual tokens.
 *
 * @param list	First node in list of tokens
 */
void	print_debug_tokens(const t_token *list)
{
	const char		*type_str;

	while (list)
	{
		type_str = get_token_type_str(list);
		ft_printf("token->value:		%s\n", list->value);
		ft_printf("token->index:		%d\n", list->index);
		ft_printf("token->type:		%s\n\n", type_str);
		list = list->next;
	}
}

/**
 * Prints out debug information for data.
 *
 * @param data	Pointer to main data struct
 */
void	print_debug(const t_minishell *data)
{
	if (!data)
	{
		ft_printf("data is NULL\n");
		return ;
	}
	ft_printf("\ndata->raw_input:	%s\n", data->raw_input);
	ft_printf("data->token_count:	%d\n", (int)data->token_count);
	ft_printf("pipes:			%d\n", (int)count_pipes(data->token_list));
	ft_printf("\n");
	print_debug_tokens(data->token_list);
}
