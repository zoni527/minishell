/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenization_01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:49:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/20 17:59:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_over_operator(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		++str;
	return (++str);
}

static const char	*skip_over_word(const char *str)
{
	char	quote_flag;

	quote_flag = '\0';
	while (*str)
	{
		if (ft_strchr(METACHARACTERS, *str) && quote_flag == '\0')
			break ;
		if (*str == '\'' || *str == '"')
			toggle_quote_flag(&quote_flag, *str);
		++str;
	}
	return (str);
}

/**
 * Lexes raw input and creates list of tokens from words
 * delimited by metacharacters.
 *
 * @param data	Pointer to main data struct
 */
void	lex_raw_input(t_minishell *data)
{
	const char	*str;
	char		*start;
	size_t		word_len;
	char		quote_flag;

	str = data->raw_input;
	quote_flag = '\0';
	while (*str)
	{
		str = ft_skip_whitespace(str);
		if (!*str)
			break ;
		start = (char *)str;
		if (ft_strchr("|<>", *str) && !quote_flag)
			str = skip_over_operator(str);
		else
			str = skip_over_word(str);
		word_len = str - start;
		tokenize(data, start, word_len);
	}
}

/**
 * Creates token from string and appends the new token to data->token_list.
 * Requests heap memory from the memarena.
 *
 * @param data		Pointer to main data struct
 * @param src		Source string to use for token creation
 * @param word_len	Amount of characters that are part of the token in src
 */
void	tokenize(t_minishell *data, const char *src, size_t len)
{
	char	*word;
	t_token	*new;

	word = ft_ma_calloc(data->arena, len + 1, sizeof(char));
	ft_strlcpy(word, src, len + 1);
	new = new_token_node(data->arena, word);
	append_token(&data->token_list, new);
}

/**
 * Prints token values in data->token_list
 *
 * @param data	Pointer to main data struct
 */
void	print_tokens(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		ft_printf("%s\n", token->value);
		token = token->next;
	}
}
