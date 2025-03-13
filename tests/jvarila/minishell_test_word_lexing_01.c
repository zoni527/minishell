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
		if (ft_strchr("|<>", *str))
		{
			if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
				str++;
			str++;
		}
		else
			while (*str && !ft_strchr(METACHARACTERS, *str))
				str++;
		tokens++;
	}
	return (tokens);
}

int	main(int argc, char *argv[])
{
	t_memarena			*arena;
	char				**tokens_array;
	char				*start;
	char				*raw_input;
	int					tokens;
	int					i;
	int					word_len;
	static t_list		lst;
	t_list				*node;

	if (argc != 2)
		return (write_error_return_int("ERROR: input one argument", 1));
	if (has_unclosed_quotes(argv[1]))
		return (write_error_return_int("ERROR: input has unclosed quotes", \
								 ERROR_UNCLOSED));
	arena = new_memarena();
	if (!arena)
		return (write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	raw_input = argv[1];
	tokens = count_tokens(raw_input);
	attempt_allocation(arena, (void **)&tokens_array, tokens + 1, sizeof(char *));
	node = &lst;
	i = -1;
	while (*raw_input)
	{
		raw_input = skip_whitespace(raw_input);
		if (!*raw_input)
			break ;
		start = raw_input;
		if (ft_strchr("|<>", *raw_input))
		{
			if (!ft_strncmp(raw_input, "<<", 2) || !ft_strncmp(raw_input, ">>", 2))
				raw_input++;
			raw_input++;
		}
		else
			while (*raw_input && !ft_strchr(METACHARACTERS, *raw_input))
				raw_input++;
		word_len = raw_input - start;
		attempt_allocation(arena, (void **)&tokens_array[++i], \
					 word_len + 1, sizeof(char));
		attempt_allocation(arena, (void **)&node->content, word_len + 1, sizeof(char));
		ft_strlcpy(tokens_array[i], start, word_len + 1);
		ft_strlcpy(node->content, start, word_len + 1);
		attempt_allocation(arena, (void **)&node->next, 1, sizeof(t_list));
		node = node->next;
	}
	i = -1;
	while (tokens_array[++i])
		ft_printf("%s\n", tokens_array[i]);
	node = &lst;
	while (node->content)
	{
		ft_printf("%s\n", node->content);
		node = node->next;
	}
	free_memarena(arena);
	return (0);
}
