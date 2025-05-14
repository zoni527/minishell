/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_02.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:05:20 by rhvidste          #+#    #+#             */
/*   Updated: 2025/05/02 13:19:35 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to parse the envp into
 * a linked list for later use
 *
 * @param data	Main data struct
 * @param envp	system envp input
 */
void	env_list_from_envp(t_minishell *data, const char **envp)
{
	t_var	*current;
	char	*vals[3];
	int		i;
	int		j;

	current = NULL;
	i = -1;
	while (envp && envp[++i])
	{
		vals[0] = ms_strdup(data, envp[i]);
		j = ft_char_index(vals[0], '=');
		vals[1] = ms_substr(data, vals[0], 0, j);
		vals[2] = ms_substr(data, vals[0],
				(j + 1), ft_strlen(vals[0]) - (j + 1));
		if (current == NULL)
		{
			current = create_new_env_var(data, vals[0], vals[1], vals[2]);
			data->minishell_env = current;
			continue ;
		}
		current->next = create_new_env_var(data, vals[0], vals[1], vals[2]);
		current->next->prev = current;
		current = current->next;
	}
	set_shell_lvl(data);
}

/**
 * Function to convert envp_list to an NULL terminated
 * array of strings
 *
 * @param data	Pointer to main data struct
 *
 * @return	NULL terminated char ** environment array from data->minishell_env
 */
char	**create_envp_arr_from_custom_env(t_minishell *data)
{
	t_var	*current;
	char	**envp_arr;
	int		list_len;
	int		i;

	i = -1;
	list_len = 0;
	list_len = get_env_list_size(data->minishell_env);
	envp_arr = ms_calloc(data, (list_len + 1), sizeof(char *));
	current = data->minishell_env;
	while (++i < list_len)
	{
		envp_arr[i] = current->raw;
		current = current->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}
