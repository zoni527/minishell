/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_word_splitting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:55:45 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/25 10:59:58 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_token(t_minishell *data, t_token *token);
static void	handle_token_split(t_minishell *data, t_token *token,
				const char **src_ptr, size_t len);
static char	*skip_over_expanded_word(const char *str);

/**
 * Loops through all tokens in data->token_list and calls split_token on them.
 * 
 * @param data	Pointer to main data struct
 */
void	word_splitting(t_minishell *data)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		split_token(data, token);
		token = token->next;
	}
}

/**
 * Loops through token->value and looks for whitespace that isn't within quotes.
 * When it finds such a character or reaches the end of the string it checks if
 * the portion to be split is smaller than the whole end of the word. If so it
 * calls handle_token_split.
 *
 * @param data	Pointer to main data struct
 * @param token	Pointer to token node to be split
 */
static void	split_token(t_minishell *data, t_token *token)
{
	const char	*str;
	char		*start;
	size_t		word_len;

	str = token->value;
	while (*str)
	{
		str = ft_skip_whitespace(str);
		if (!*str)
			break ;
		start = (char *)str;
		str = skip_over_expanded_word(str);
		word_len = str - start;
		if (word_len != ft_strlen(start))
			handle_token_split(data, token, &str, word_len);
	}
}

/**
 * Creates a substring from token->value using len as the length of the
 * substring. Function also updates the string pointed to by str_ptr so
 * that the progression in split_token is correct.
 *
 * If the token split is the first element in data->token list, updates
 * the first element to be the new node.
 *
 * @param data		Pointer to main data struct
 * @param token		Pointer to token node to be split
 * @param src_ptr	Pointer to traversal string
 * @param len		Length of substring
 */
static void	handle_token_split(t_minishell *data, t_token *token,
					const char **src_ptr, size_t len)
{
	char	*word;
	t_token	*new;
	char	*remaining;

	word = ft_ma_substr(data->arena, token->value, 0, len);
	new = new_token_node(data, word);
	insert_token_left(token, new);
	remaining = ft_ma_substr(data->arena, token->value, len,
			ft_strlen(token->value + len));
	token->value = ft_skip_whitespace(remaining);
	*src_ptr = token->value;
	if (data->token_list == token)
		data->token_list = new;
}

/**
 * Looks for whitespace that is not within quotes to delimit words.
 *
 * @param str	String to be traversed
 *
 * @return		Position in string where a whitespace character outsife of
 *				quotes was found, or the end of the string
 */
static char	*skip_over_expanded_word(const char *str)
{
	char	quote_flag;

	quote_flag = '\0';
	while (*str)
	{
		if (ft_isspace(*str) && quote_flag == '\0')
			break ;
		if (*str == '\'' || *str == '"')
			toggle_quote_flag(&quote_flag, *str);
		++str;
	}
	return ((char *)str);
}
