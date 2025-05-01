/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:55:52 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/11 15:19:51 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to call the UNSET builtin
 *
 * @param data	pointer to the main data struct
 */
void	builtin_unset(t_minishell *data)
{
	t_token	*tokens;

	tokens = copy_cmd_and_args_within_pipe(data);
	tokens = tokens->next;
	while (tokens)
	{
		remove_env(tokens->value, data->minishell_env);
		tokens = tokens->next;
	}
	data->last_rval = 0;
}
