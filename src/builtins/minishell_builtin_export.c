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

static bool	is_valid_key(t_token *token)
{
	if (ft_isalpha(token->value[0]) || token->value[0] == '_')
		return (true);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(token->value, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (false);
}

/**
 * Function to set key and value
 *
 * @param data	main data struct
 * @param token	token reference
 */
static void	set_key_and_value(t_minishell *data, t_token *token)
{
	char	*key;
	char	*value;
	int		i;

	while (token && token->type == ARGUMENT)
	{
		if (is_valid_key(token))
		{
			i = ft_char_index(token->value, '=');
			if (i == -1)
			{
				key = ft_ma_strdup(data->arena, token->value);
				value = "\0";
			}
			else
			{
				key = ft_ma_substr(data->arena, token->value, 0, i);
				value = ft_ma_substr(data->arena, token->value,
						(i + 1), (ft_strlen(token->value) - (i + 1)));
			}
			ms_setenv_export(data, key, value, token->value);
		}
		token = token->next;
	}
}

/**
 * Function to call the EXPORT builtin
 *
 * @param data	pointer to teh main data struct
 * @param builtin_token	pointer to the root builtin token
 * @param envp	pinter to the fist envp element
 */
void	builtin_export(t_minishell *data, t_token *token)
{
	if (token)
		token = token->next;
	if (token == NULL)
	{
		print_env_alphabetically(data);
		return ;
	}
	set_key_and_value(data, token);
	data->last_rval = 0;
}
