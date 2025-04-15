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
 */
int	builtins(t_minishell *data)
{
	t_token	*builtin_token;

	builtin_token = fetch_builtin(data);
	if (builtin_token)
	{
		if (ft_strncmp(builtin_token->value, "echo", 4) == 0)
			builtin_echo(data, builtin_token);
		if (ft_strncmp(builtin_token->value, "cd", 2) == 0)
			builtin_cd(data, builtin_token, data->minishell_env);
		if (ft_strncmp(builtin_token->value, "pwd", 3) == 0)
			builtin_pwd(data);
		if (ft_strncmp(builtin_token->value, "export", 6) == 0)
			builtin_export(data, builtin_token, data->minishell_env);
		if (ft_strncmp(builtin_token->value, "unset", 5) == 0)
			builtin_unset(data, builtin_token, data->minishell_env);
		if (ft_strncmp(builtin_token->value, "env", 3) == 0)
			builtin_env(data);
		if (ft_strncmp(builtin_token->value, "exit", 4) == 0)
		{
			if (builtin_exit(data, builtin_token) == NO_EXIT)
				return (ERROR_BLTN_NO_EXIT);
			return (0);
		}
	}
	return (1);
}
