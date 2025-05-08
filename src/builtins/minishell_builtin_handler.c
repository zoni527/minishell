/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:28:33 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/09 17:05:22 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to fetch builtin token
 * returns NULL if none found
 *
 * @param data	main data struct
 *
 * @return	First builtin token in data->token_list, NULL no builtin found
 */
t_token	*fetch_builtin(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	if (data->pipe_count == 0)
	{
		while (token)
		{
			if (token->type == BUILTIN)
				return (token);
			token = token->next;
		}
	}
	return (NULL);
}

/**
 * Function to handle and reroute builtins
 *
 * @param data	main data struct
 *
 * @return EXIT_SUCCESS if builtin is matched and run, EXIT_FAILURE if not
 */
int	builtins(t_minishell *data)
{
	t_token	*builtin_token;

	builtin_token = fetch_builtin(data);
	if (!builtin_token)
		return (EXIT_FAILURE);
	if (get_builtin_type(builtin_token) == BLTN_ECHO)
		builtin_echo(data);
	else if (get_builtin_type(builtin_token) == BLTN_CD)
		builtin_cd(data);
	else if (get_builtin_type(builtin_token) == BLTN_PWD)
		builtin_pwd(data);
	else if (get_builtin_type(builtin_token) == BLTN_EXPORT)
		builtin_export(data);
	else if (get_builtin_type(builtin_token) == BLTN_UNSET)
		builtin_unset(data);
	else if (get_builtin_type(builtin_token) == BLTN_ENV)
		builtin_env(data);
	else if (get_builtin_type(builtin_token) == BLTN_EXIT)
		builtin_exit(data);
	return (EXIT_SUCCESS);
}
