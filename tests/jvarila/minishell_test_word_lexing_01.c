/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_word_lexing_01.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/12 15:16:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	attempt_allocation(t_memarena *arena, void **target, \
						size_t nmemb, size_t size)
{
	*target = memarena_calloc(arena, nmemb, size);
	if (!*target)
	{
		free_memarena(arena);
		ft_putendl_fd(MSG_ERROR_ALLOC, STDERR_FILENO);
		exit(ERROR_ALLOC);
	}
}

char	*skip_operator(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		str++;
	str++;
	return ((char *)str);
}

size_t	count_tokens(const char *str)
{
	size_t	tokens;
	
	if (!str)
		return (0);
	tokens = 0;
	while (*str)
	{
		str = skip_whitespace(str);
		if (!*str)
			break ;
		if (*str == '"' || *str == '\'')
			str = ft_strchr(str + 1, *str) + 1;
		else if (ft_strchr("|<>", *str))
			str = skip_operator(str);
		else
			while (*str && *str != '"' && *str != '\'' \
				&& !ft_strchr(METACHARACTERS, *str))
				str++;
		tokens++;
	}
	return (tokens);
}

int	main(int argc, char *argv[])
{
	t_memarena	*arena;
	char		**words;
	char		*start_pos;
	char		*str;
	int			wc;
	int			word_len;

	if (argc != 2)
		return (write_error_return_int("ERROR: input one argument", 1));
	if (has_unclosed_quotes(argv[1]))
		return (write_error_return_int("ERROR: input has unclosed quotes", \
								 ERROR_UNCLOSED));
	arena = new_memarena();
	if (!arena)
		return (write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	attempt_allocation(arena, (void **)&words, 100, sizeof(char *));
	str = argv[1];
	wc = 0;
	while (*str)
	{
		str = skip_whitespace(str);
		// Ignore everything within quotes
		if (*str == '"' || *str == '\'')
		{
			wc++;
			start_pos = str;
			str = ft_strchr(str + 1, *str) + 1;
			word_len = str - start_pos;
			ft_printf("Current position in input: %s\n", start_pos);
			ft_printf("Current word length: %d\n", word_len);
			attempt_allocation(arena, (void *)&words[wc - 1], word_len + 1, sizeof(char));
			ft_strlcpy(words[wc - 1], start_pos, word_len + 1);
			ft_printf("Word: %s\n", words[wc -1]);
			continue ;
		}
		// When encountering a metacharacter if it is an operator count it
		// as a word, skip whitescpae
		if (ft_strchr(METACHARACTERS, *str))
		{
			wc++;
			start_pos = str;
			if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
				str++;
			str++;
			word_len = str - start_pos;
			ft_printf("Current position in input: %s\n", start_pos);
			ft_printf("Current word length: %d\n", word_len);
			attempt_allocation(arena, (void *)&words[wc - 1], word_len + 1, sizeof(char));
			ft_strlcpy(words[wc - 1], start_pos, word_len + 1);
			ft_printf("Word: %s\n", words[wc -1]);
			continue ;
		}
		wc++;
		start_pos = str;
		while (*str && *str != '"' && *str != '\'' \
			&& !ft_strchr(METACHARACTERS, *str))
			str++;
		word_len = str - start_pos;
		ft_printf("Current position in input: %s\n", start_pos);
		ft_printf("Current word length: %d\n", word_len);
		attempt_allocation(arena, (void *)&words[wc - 1], word_len + 1, sizeof(char));
		ft_strlcpy(words[wc - 1], start_pos, word_len + 1);
		ft_printf("Word: %s\n", words[wc -1]);
	}
	ft_printf("Found %d words in input %s\n", wc, argv[1]);
	free_memarena(arena);
	return (0);
}
