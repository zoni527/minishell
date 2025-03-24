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

/**
 * Lexes raw input and creates list of tokens from words
 * delimited by metacharacters.
 *
 * @param data	Pointer to main data struct
 */
void	lex_raw_input(t_minishell *data)
{
	const char	*raw_input;
	char		*start;
	size_t		word_len;

	raw_input = data->raw_input;
	while (*raw_input)
	{
		raw_input = ft_skip_whitespace(raw_input);
		if (!*raw_input)
			break ;
		start = (char *)raw_input;
		if (ft_strchr("|<>", *raw_input))
		{
			if (!ft_strncmp(raw_input, "<<", 2) \
				|| !ft_strncmp(raw_input, ">>", 2))
				raw_input++;
			raw_input++;
		}
		else
			while (*raw_input && !ft_strchr(METACHARACTERS, *raw_input))
				raw_input++;
		word_len = raw_input - start;
		tokenize_word(data, start, word_len);
	}
}

/**
 * Creates token from word and appends the new token to data->token_list.
 * Requests heap memory from the memarena.
 *
 * @param data		Pointer to main data struct
 * @param src		Source string to use for token creation
 * @param word_len	Amount of characters that are part of the token in src
 */
void	tokenize_word(t_minishell *data, const char *src, size_t word_len)
{
	char	*word;
	t_token	*new;

	word = ft_ma_calloc(data->arena, word_len + 1, sizeof(char));
	ft_strlcpy(word, src, word_len + 1);
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
