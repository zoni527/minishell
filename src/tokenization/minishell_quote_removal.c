/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quote_removal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:47:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/26 18:53:09 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		remove_quotes_from_token(t_minishell *data, t_token *token);
static size_t	remove_quotes_at_index(t_minishell *data, t_token *token, \
									char quote, size_t i);

void	quote_removal(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		remove_quotes_from_token(data, token);
		token = token->next;
	}
}

static void	remove_quotes_from_token(t_minishell *data, t_token *token)
{
	char		quote_flag;
	size_t		i;

	quote_flag = '\0';
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' || token->value[i] == '"')
			quote_flag = token->value[i];
		if (quote_flag != '\0')
		{
			i = remove_quotes_at_index(data, token, quote_flag, i);
			quote_flag = '\0';
		}
		++i;
	}
}

static size_t	remove_quotes_at_index(t_minishell *data, t_token *token, \
									char quote, size_t i)
{
	size_t	quote_index;
	char	*within_quotes;
	size_t	within_quotes_len;
	char	*result;

	quote_index = i++;
	while (token->value[i] != quote)
		++i;
	within_quotes_len = i - quote_index - 1;
	within_quotes = ft_ma_substr(data->arena, token->value, \
							quote_index + 1, within_quotes_len);
	result = ft_ma_substr(data->arena, token->value, 0, quote_index);
	result = ft_ma_strjoin(data->arena, result, within_quotes);
	result = ft_ma_strjoin(data->arena, result, &token->value[i + 1]);
	token->value = result;
	return (i - 2);
}
