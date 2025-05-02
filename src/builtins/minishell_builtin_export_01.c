/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:53:52 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/11 15:03:17 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to call the EXPORT builtin
 *
 * @param data	pointer to the main data struct
 */
void	builtin_export(t_minishell *data)
{
	t_token	*tokens;

	tokens = copy_cmd_and_args_within_pipe(data);
	tokens = tokens->next;
	if (tokens == NULL)
	{
		print_env_alphabetically(data);
		return ;
	}
	while (tokens)
	{
		set_key_and_value(data, tokens);
		tokens = tokens->next;
	}
	data->last_rval = 0;
}
