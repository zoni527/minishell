/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quote_removal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:47:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/21 17:42:26 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes_from_token(t_minishell *data, t_token *token);
size_t	remove_quotes_at_index(t_minishell *data, t_token *token, \
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

void	remove_quotes_from_token(t_minishell *data, t_token *token)
{
	char		quote;
	size_t		i;
	char		*result;

	quote = 0;
	result = NULL;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' || token->value[i] == '"')
			quote = token->value[i];
		if (quote != 0)
		{
			i = remove_quotes_at_index(data, token, quote, i);
			toggle_quote_flag(&quote, quote);
		}
		++i;
	}
}

size_t	remove_quotes_at_index(t_minishell *data, t_token *token, \
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
