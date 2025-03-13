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

t_list	*new_token_node(t_memarena *arena, const char *str)
{
	t_list	*node;

	attempt_allocation(arena, (void **)&node, 1, sizeof(t_list));
	attempt_allocation(arena, (void **)&node->content, 1, sizeof(t_token));
	((t_token *)node->content)->value = str;
	if (*str == '|')
		((t_token *)node->content)->type = PIPE;
	else if (ft_strncmp(str, "<", 2) == 0)
		((t_token *)node->content)->type = REDIRECT_INPUT;
	else if (ft_strncmp(str, ">", 2) == 0)
		((t_token *)node->content)->type = REDIRECT_OUTPUT;
	else if (ft_strncmp(str, "<<", 3) == 0)
		((t_token *)node->content)->type = HEREDOC;
	else if (ft_strncmp(str, ">>", 3) == 0)
		((t_token *)node->content)->type = APPEND;
	else
		((t_token *)node->content)->type = WORD;
	return (node);
}

void	skip_over_operator(const char **str)
{
	if (!ft_strncmp(*str, "<<", 2) || !ft_strncmp(*str, ">>", 2))
		(*str)++;
	(*str)++;
}

void	build_initial_token_list(t_minishell *data)
{
	t_list		*node;
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
		attempt_allocation(data->arena, (void **)&word, word_len, sizeof(char));
		ft_strlcpy(word, str, word_len + 1);
		node = new_token_node(data->arena, word);
		ft_lstadd_back(&data->token_list, node);
	}
}

int	main(int argc, char *argv[])
{
	t_memarena	*arena;
	char		**tokens_array;
	char		*start;
	char		*raw_input;
	char		*word;
	int			tokens;
	int			i;
	int			word_len;
	t_list		*lst;
	t_list		*node;

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
	lst = NULL;
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
		attempt_allocation(arena, (void **)&word, word_len, sizeof(char));
		node = new_token_node(arena, word);
		ft_lstadd_back(&lst, node);
	}
	i = -1;
	while (tokens_array[++i])
		ft_printf("%s\n", tokens_array[i]);
	node = &lst;
	ft_printf("\n");
	while (node->content)
	{
		ft_printf("%s\n", node->content);
		node = node->next;
	}
	free_memarena(arena);
	return (0);
}
