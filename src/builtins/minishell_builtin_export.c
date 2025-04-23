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
 * Helper Function to prepare root token
 * before handing to the main function.
 *
 * @param data	main data struct
 * @param builtin_token	token reference
 */
static t_token	*proccess_token(t_minishell *data, t_token *token)
{
	if (token->next == NULL)
	{
		data->last_rval = EXIT_SUCCESS;
		return (NULL);
	}
	else
	{
		token = token->next;
		return (token);
	}
	return (NULL);
}

static void	set_key_and_value(t_minishell *data, t_token *token, t_var *envp)
{
	char	*key;
	char	*value;
	int		i;

	i = ft_char_index(token->value, '=');
	if (i == -1)
	{
		key = ft_ma_strdup(data->arena, token->value);
		value = NULL;
	}
	else
	{
		key = ft_ma_substr(data->arena, token->value, 0, i);
		value = ft_ma_substr(data->arena, token->value, \
						(i + 1), (ft_strlen(token->value) - (i + 1)));
	}
	ms_setenv(data, key, value, envp);
}

/**
 * Function to call the EXPORT builtin
 *
 * @param data	pointer to teh main data struct
 * @param builtin_token	pointer to the root builtin token
 * @param envp	pinter to the fist envp element
 */
void	builtin_export(t_minishell *data, t_token *builtin_token)
{
	t_token	*token;

	token = builtin_token;
	token = proccess_token(data, token);
	if (token == NULL)
	{
		print_env_alphabetically(data, envp);
		data->last_rval = EXIT_SUCCESS;
		return ;
	}
	set_key_and_value(data, token, envp);
	data->last_rval = EXIT_SUCCESS;
}
