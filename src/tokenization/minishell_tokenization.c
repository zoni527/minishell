/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:49:09 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 16:04:54 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lex_raw_input(t_minishell *data);
static void	tokenize(t_minishell *data, const char *src, size_t len);
static char	*skip_over_operator(const char *str);
static char	*skip_over_word(const char *str);

/**
 * Calls functions to complete the tokenization process steps.
 *
 * @param data	Pointer to main data struct
 */
void	tokenization(t_minishell *data)
{
	lex_raw_input(data);
	variable_expansion(data);
	word_splitting(data);
	quote_removal(data);
	token_classification(data);
	assign_token_indices(data);
	data->token_count = count_tokens(data->token_list);
	data->pipe_count = count_pipes(data->token_list);
	data->hd_count = count_heredocs(data->token_list);
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

	word = ms_substr(data, src, 0, len);
	new = new_token_node(data, word);
	append_token(&data->token_list, new);
}

/**
 * Helper function to skip over operators in strings. Takes into account
 * << and >> as special cases as they have two characters instead of one
 * (vs |<>).
 *
 * @param str	String whose first character is part of an operator
 *
 * @return	String position past an operator
 */
static char	*skip_over_operator(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		++str;
	return ((char *)++str);
}

/**
 * Helper function to correctly skip over words, taking into account quotes.
 * Breaks when it finds a metacharacter that is not within quotes.
 *
 * @param str	String containing raw input
 *
 * @return	String position past one word
 */
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
