/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:48:53 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/19 12:16:03 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Top level function for starting variable expansion for all tokens in 
 * data->token_list.
 *
 * @param data	Pointer to main data struct
 */
void	variable_expansion(t_minishell *data)
{
	char	*str;
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		str = ft_strchr(token->value, '$');
		if (!str)
		{
			token = token->next;
			continue ;
		}
		expand_variables(data, token);
		token = token->next;
	}
}

/**
 * Function goes throug token and calls expand_variable for ech expandable
 * variable it finds.
 *
 * @param data	Pointer to main data struct
 * @param token	Token to expand
 */
void	expand_variables(t_minishell *data, t_token *token)
{
	t_var		*var;
	bool		within_single_quotes;
	size_t		i;

	i = 0;
	while (contains_unexpanded_variable(token))
	{
		while (ft_isspace(token->value[i]))
			++i;
		if (token->value[i] == '\'')
			ft_toggle_bool(&within_single_quotes);
		if (token->value[i] == '$' && !ft_isspace(token->value[i + 1]) \
			&& !within_single_quotes)
		{
			var = find_var(data, &token->value[++i]);
			i = expand_variable(data, token, var, i);
			continue ;
		}
		++i;
	}
}

/**
 * Expands a single variable inside a given token.
 * 
 * @param data		Pointer to main data struct
 * @param token		Token that contains unexpanded variable
 * @param var		Variable used for expansion
 * @param var_index	Index of first character after '$', also corresponds to
 *					"len before '$'" + 1, which can be used in ft_strlcat to
 *					concatenate everything before '$'
 */
size_t	expand_variable(t_minishell *data, t_token *token, t_var *var, \
					size_t var_index)
{
	char	*new;
	size_t	old_len;
	size_t	new_len;
	size_t	unexpanded_len;
	size_t	expanded_len;

	if (!var)
	{
		unexpanded_len = ft_strlen(&token->value[var_index]);
		expanded_len = 0;
	}
	else
	{
		unexpanded_len = ft_strlen(var->key);
		expanded_len = ft_strlen(var->value);
	}
	old_len = ft_strlen(token->value);
	new_len = old_len - 1 - unexpanded_len + expanded_len;
	new = memarena_calloc(data->arena, new_len + 1, sizeof(char));
	ft_strlcat(new, token->value, var_index);
	if (var)
		ft_strlcat(new, var->value, new_len + 1);
	ft_strlcat(new, &token->value[var_index] + unexpanded_len, new_len + 1);
	token->value = new;
	return (var_index + expanded_len - 1);
}

/**
 * Function for checking if token contains an unexpanded variable.
 * <p>
 * Takes into account single quotes and requires the first character after '$'
 * to be non whitespace.
 *
 * @param token	Token to check
 */
bool	contains_unexpanded_variable(t_token *token)
{
	const char	*str;
	bool		within_single_quotes;

	str = token->value;
	within_single_quotes = false;
	while (str)
	{
		str = ft_skip_whitespace(str);
		if (!*str)
			break ;
		if (*str == '\'')
		{
			ft_toggle_bool(&within_single_quotes);
			str++;
			continue ;
		}
		if (*str == '$' && *(str + 1) \
			&& !ft_isspace(*(str + 1)) \
			&& !within_single_quotes)
			return (true);
		str++;
	}
	return (false);
}

/**
 * Looks through custom_env in data for a variable whose key matches the
 * argument str.
 *
 * @param data	Pointer to main data struct
 * @param str	String that points to the first character of the variable name
 *				(the first character after the char '$')
 */
t_var	*find_var(t_minishell *data, const char *str)
{
	t_var	*var;
	size_t	len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]) \
		&& (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	var = data->custom_env;
	while (var)
	{
		if (ft_strncmp(var->key, str, len + 1) == 0)
			return (var);
		var = var->next;
	}
	return (NULL);
}
