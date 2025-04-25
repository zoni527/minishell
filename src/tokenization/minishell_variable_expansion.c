/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_variable_expansion.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:48:53 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/21 10:03:01 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		expand_variables(t_minishell *data, t_token *token);
static size_t	expand_variable(t_minishell *data, t_token *token, t_var *var,
					size_t var_index);
static t_var	*find_var(t_minishell *data, const char *str);
static t_var	*question_mark_variable(t_minishell *data);

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
static void	expand_variables(t_minishell *data, t_token *token)
{
	t_var		*var;
	char		quote_flag;
	size_t		i;

	quote_flag = 0;
	i = 0;
	while (token->value[i])
	{
		while (ft_isspace(token->value[i]))
			++i;
		if (token->value[i] == '\'' || token->value[i] == '"')
			toggle_quote_flag(&quote_flag, token->value[i]);
		else if (token->value[i] == '$' && !ft_isspace(token->value[i + 1])
			&& !(quote_flag == '\'') && !is_heredoc(token->prev))
		{
			if (token->value[++i] == '?')
				var = question_mark_variable(data);
			else
				var = find_var(data, &token->value[i]);
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
 * @return			Returns index for updated token->value so that expansion
 *					can continue at the right spot
 */
static size_t	expand_variable(t_minishell *data, t_token *token, t_var *var,
					size_t var_index)
{
	char	*new;
	size_t	old_len;
	size_t	new_len;
	size_t	unexpanded_len;
	size_t	expanded_len;

	if (!var)
	{
		unexpanded_len = var_name_len(&token->value[var_index]);
		expanded_len = 0;
	}
	else
	{
		unexpanded_len = ft_strlen(var->key);
		expanded_len = ft_strlen(var->value);
	}
	old_len = ft_strlen(token->value);
	new_len = old_len - 1 - unexpanded_len + expanded_len;
	new = ft_ma_calloc(data->arena, new_len + 1, sizeof(char));
	ft_strlcat(new, token->value, var_index);
	if (var)
		ft_strlcat(new, var->value, new_len + 1);
	ft_strlcat(new, &token->value[var_index] + unexpanded_len, new_len + 1);
	token->value = new;
	return (var_index + expanded_len - 1);
}

/**
 * Looks through minishell_env in data for a variable whose key matches the
 * argument str.
 *
 * @param data	Pointer to main data struct
 * @param str	String that points to the first character of the variable name
 *				(the first character after the char '$')
 * @return		Returns variable on a match, NULL if no matching variable can
 *				be found in data->custom_env
 */
static t_var	*find_var(t_minishell *data, const char *str)
{
	t_var	*var;
	size_t	len;

	len = var_name_len(str);
	var = data->minishell_env;
	while (var)
	{
		if (len == ft_strlen(var->key)
			&& ft_strncmp(var->key, str, len) == 0)
			return (var);
		var = var->next;
	}
	return (NULL);
}

/**
 * Creates a t_var node with the correct values to perform expansion for $?.
 * Basically this function uses a modified version of itoa to assign
 * data->last_rval to variable->value.
 *
 * @param data	Pointer to main data struct
 */
static t_var	*question_mark_variable(t_minishell *data)
{
	t_var	*variable;
	int		str_len;
	int		last_rval;

	variable = ft_ma_calloc(data->arena, 1, sizeof(t_var));
	variable->key = "?";
	last_rval = (unsigned char)data->last_rval;
	str_len = ft_int_digits(last_rval);
	variable->value = ft_ma_calloc(data->arena, str_len + 1, sizeof(char));
	while (--str_len)
	{
		variable->value[str_len] = (last_rval % 10) + '0';
		last_rval /= 10;
	}
	variable->value[0] = (last_rval % 10) + '0';
	return (variable);
}
