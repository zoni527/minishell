/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_set_key_and_value.c       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:07:36 by rhvidste          #+#    #+#             */
/*   Updated: 2025/05/02 16:10:05 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * Function to handle NO equals case
 * from the EXPORT builtin
 * set key and value function
 *
 * @param data	main data struct
 * @param token	token reference
 */
static void	handle_no_equals(t_minishell *data, t_token *token)
{
	char	*raw;
	char	*key;
	char	*value;

	raw = token->value;
	key = ft_ma_strdup(data->arena, token->value);
	if (ms_getenv(data, key) != NULL)
		return ;
	value = "\0";
	ms_setenv_export(data, key, value, raw);
}

/**
 * Function to handle append case
 * from the EXPORT builtin
 * set key and value function
 *
 * @param data	main data struct
 * @param token	token reference
 * @param i	index of the equals sign
 */
static	void	handle_append(t_minishell *data, t_token *token, int i)
{
	char	*raw;
	char	*key;
	char	*value;
	char	*value2;

	key = ft_ma_substr(data->arena, token->value, 0, (i - 1));
	if (token->value[i + 1] == '\0' && ms_getenv(data, key) == NULL)
	{
		value = "\0";
	}
	else if (ms_getenv(data, key) == NULL && token->value[i + 1] != '\0')
	{
		value = ft_ma_substr(data->arena, token->value,
				(i + 1), (ft_strlen(token->value) - (i + 1)));
	}
	else
	{
		value = ms_getenv(data, ft_ma_substr(data->arena,
					token->value, 0, i -1));
		value2 = ft_ma_substr(data->arena, token->value, (i + 1),
				ft_strlen(token->value) - (i + 1));
		value = ft_ma_strjoin(data->arena, value, value2);
	}
	raw = create_raw(data, key, value);
	ms_setenv_export(data, key, value, raw);
}

/**
 * Function to handle equals case
 * from the EXPORT builtin
 * set key and value function
 *
 * @param data	main data struct
 * @param token	token reference
 * @param i	index of the equals sign
 */
static void	handle_equals(t_minishell *data, t_token *token, int i)
{
	char	*raw;
	char	*key;
	char	*value;

	raw = token->value;
	key = ft_ma_substr(data->arena, token->value, 0, i);
	value = ft_ma_substr(data->arena, token->value,
			(i + 1), (ft_strlen(token->value) - (i + 1)));
	ms_setenv_export(data, key, value, raw);
}

/**
 * Function to check if key is valid
 *
 * @param token	token reference
 */
static bool	is_valid_key(t_token *token)
{
	int	i;

	i = 0;
	if ((ft_isalpha(token->value[i]) == 0 && token->value[i] != '_'))
		return (false);
	i++;
	while (token->value[i] && token->value[i] != '=')
	{
		if (token->value[i] == '+' && token->value[i + 1] == '=')
			return (true);
		if (ft_isalnum(token->value[i]) == 0 && token->value[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * Function to set key and value
 *
 * @param data	main data struct
 * @param token	token reference
 */
int	set_key_and_value(t_minishell *data, t_token *token)
{
	int		i;

	if (is_valid_key(token))
	{
		i = ft_char_index(token->value, '=');
		if (i == -1)
			handle_no_equals(data, token);
		else if (token->value[i - 1] == '+')
			handle_append(data, token, i);
		else
			handle_equals(data, token, i);
	}
	else
	{
		ft_putstr_fd(STR_PROMPTSTART "export: `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		data->last_rval = EXIT_BLTN_INVALIDID;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
