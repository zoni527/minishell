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

void	add_token_to_end(t_token **list, t_token *token)
{
	t_token	*end;

	if (!*list)
	{
		*list = token;
		return ;
	}
	end = *list;
	while (end->next)
		end = end->next;
	end->next = token;
	if (token)
	{
		token->prev = end;
		token->id = end->id + 1;
	}
}

void	insert_token_right(t_token *current, t_token *new)
{
	t_token	*next;

	if (!current || !new)
		return ;
	next = current->next;
	if (next)
		next->prev = new;
	current->next = new;
	new->prev = current;
	new->next = next;
}

void	insert_token_left(t_token *current, t_token *new)
{
	t_token	*prev;

	if (!current || !new)
		return ;
	prev = current->prev;
	if (prev)
		prev->next = new;
	current->prev = new;
	new->prev = prev;
	new->next = current;
}

/**
 * DESCRIPTION
 *     The initial token count treats "|<> \t\n" as separating characters,
 *     later words will be expanded and split which will impact the count.
 */
size_t	count_tokens(const char *str)
{
	size_t	count;
	
	if (!str)
		return (0);
	count = 0;
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
		count++;
	}
	return (count);
}

t_token	*new_token_node(t_memarena *arena, const char *str)
{
	t_token	*token;

	token = memarena_calloc(arena, 1, sizeof(t_token));
	token->value = str;
	if (*str == '|')
		token->type = PIPE;
	else if (ft_strncmp(str, "<", 2) == 0)
		token->type = REDIRECT_INPUT;
	else if (ft_strncmp(str, ">", 2) == 0)
		token->type = REDIRECT_OUTPUT;
	else if (ft_strncmp(str, "<<", 3) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(str, ">>", 3) == 0)
		token->type = APPEND;
	else
		token->type = WORD;
	return (token);
}

void	skip_over_operator(const char **str)
{
	if (!ft_strncmp(*str, "<<", 2) || !ft_strncmp(*str, ">>", 2))
		(*str)++;
	(*str)++;
}

void	build_initial_token_list(t_minishell *data)
{
	t_token		*node;
	const char	*str;
	const char	*start;
	char		*word;
	size_t		word_len;

	str = data->raw_input;
	while (*str)
	{
		str = skip_whitespace(str);
		if (!*str)
			break ;
		start = str;
		if (ft_strchr("|<>", *str))
			skip_over_operator(&str);
		else
			while (*str && !ft_strchr(METACHARACTERS, *str))
				str++;
		word_len = str - start;
		word = memarena_calloc(data->arena, word_len + 1, sizeof(char));
		ft_strlcpy(word, str, word_len + 1);
		node = new_token_node(data->arena, word);
		add_token_to_end(&data->token_list, node);
	}
}

void	parse_word(t_minishell *data, const char *src, size_t word_len)
{
	char	*word;
	t_token	*new;

	word = memarena_calloc(data->arena, word_len + 1, sizeof(char));
	ft_strlcpy(word, src, word_len + 1);
	new = new_token_node(data->arena, word);
	add_token_to_end(&data->token_list, new);
}

void	parse_raw_input(t_minishell *data)
{
	const char	*raw_input;
	char		*start;
	size_t		word_len;

	raw_input = data->raw_input;
	while (*raw_input)
	{
		raw_input = skip_whitespace(raw_input);
		if (!*raw_input)
			break ;
		start = (char *)raw_input;
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
		parse_word(data, start, word_len);
	}
}

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

int	main(int argc, char *argv[])
{
	static t_minishell	data;
	t_token				*token;

	if (argc != 2)
		return (write_error_return_int("ERROR: input one argument", 1));
	if (has_unclosed_quotes(argv[1]))
		return (write_error_return_int("ERROR: input has unclosed quotes", \
								 ERROR_UNCLOSED));
	data.arena = new_memarena();
	if (!data.arena)
		return (write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	data.raw_input = argv[1];
	data.token_count = count_tokens(data.raw_input);
	data.token_list = NULL;
	parse_raw_input(&data);
	free_memarena(data.arena);
	return (0);
}
