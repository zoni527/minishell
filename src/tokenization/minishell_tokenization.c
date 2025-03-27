/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:49:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 09:53:01 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lex_raw_input(t_minishell *data);
static void	tokenize(t_minishell *data, const char *src, size_t len);
static char	*skip_over_operator(const char *str);
static char	*skip_over_word(const char *str);

void	tokenization(t_minishell *data)
{
	lex_raw_input(data);
	variable_expansion(data);
	word_splitting(data);
	quote_removal(data);
	token_classification(data);
	assign_token_indices(data);
	data->token_count = count_tokens(data->token_list);
}

/**
 * Lexes raw input and creates list of tokens from words
 * delimited by metacharacters.
 *
 * @param data	Pointer to main data struct
 */
static void	lex_raw_input(t_minishell *data)
{
	const char	*str;
	char		*start;
	size_t		word_len;

	str = data->raw_input;
	while (*str)
	{
		str = ft_skip_whitespace(str);
		if (!*str)
			break ;
		start = (char *)str;
		if (ft_strchr("|<>", *str))
			str = skip_over_operator(str);
		else
			str = skip_over_word(str);
		word_len = str - start;
		tokenize(data, start, word_len);
	}
}

/**
 * Creates token from string and appends the new token to data->token_list.
 * <p>
 * Requests heap memory from the memarena.
 *
 * @param data		Pointer to main data struct
 * @param src		Source string to use for token creation
 * @param word_len	Amount of characters that are part of the token in src
 */
static void	tokenize(t_minishell *data, const char *src, size_t len)
{
	char	*word;
	t_token	*new;

	word = ft_ma_substr(data->arena, src, 0, len);
	new = new_token_node(data->arena, word);
	append_token(&data->token_list, new);
}

static char	*skip_over_operator(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		++str;
	return ((char *)++str);
}

static char	*skip_over_word(const char *str)
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
	return ((char *)str);
}
