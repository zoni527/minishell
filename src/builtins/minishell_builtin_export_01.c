/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_01.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:53:52 by rhvidste          #+#    #+#             */
/*   Updated: 2025/05/05 14:05:10 by jvarila          ###   ########.fr       */
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
	bool	problem_with_variable;

	problem_with_variable = false;
	tokens = copy_cmd_and_args_within_pipe(data);
	tokens = tokens->next;
	if (tokens == NULL)
	{
		print_env_alphabetically(data);
		return ;
	}
	while (tokens)
	{
		if (set_key_and_value(data, tokens) == EXIT_FAILURE)
			problem_with_variable = true;
		tokens = tokens->next;
	}
	if (!problem_with_variable)
		data->last_rval = 0;
}
