/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:01:54 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/09 11:34:53 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	contains_heredoc(t_token *list)
{
	return (tokens_contain(list, is_heredoc));
}

bool	pipe_has_heredoc(const t_minishell *data)
{
	return (pipe_has(data, is_heredoc));
}

void	create_heredoc_delimiters(t_minishell *data)
{
	t_token	*token;
	size_t	i;

	data->hd_delimiters = ft_ma_calloc(data->arena, \
										data->hd_count + 1, \
										sizeof(char *));
	token = skip_to_heredoc(data->token_list);
	i = 0;
	while (i < data->hd_count)
	{
		data->hd_delimiters[i] = token->next->value;
		token = skip_to_heredoc(token->next);
		++i;
	}
}

void	setup_heredoc_file_names(t_minishell *data)
{
	char	*file_name;
	size_t	i;

	data->hd_file_names = ft_ma_calloc(data->arena, \
										data->hd_count + 1, \
										sizeof(char *));
	i = 0;
	while (i < data->hd_count)
	{
		file_name = ft_ma_calloc(data->arena, 3, sizeof(char));
		if (i >= 10)
			file_name[0] = '0' + i / 10;
		else
			file_name[0] = '0';
		file_name[1] = '0' + i % 10;
		file_name = ft_ma_strjoin(data->arena, "/tmp/minishell_heredoc_", \
							file_name);
		data->hd_file_names[i] = file_name;
		++i;
	}
}

char	*read_heredoc_input(t_minishell *data, const char *delimiter)
{
	char		*line;
	char		*result;
	bool		received_delim;

	result = "";
	received_delim = false;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			received_delim = true;
			free(line);
			break ;
		}
		result = ft_ma_strjoin(data->arena, result, line);
		result = ft_ma_strjoin(data->arena, result, "\n");
		free(line);
	}
	if (!received_delim)
		handle_error(data, "heredoc", ERROR_NODELIM);
	return (result);
}

int	run_heredoc(t_minishell *data, int index)
{
	const char	*delimiter;
	const char	*input;
	int			fd;
	int			input_len;

	delimiter = data->hd_delimiters[index];
	input = read_heredoc_input(data, delimiter);
	input_len = ft_strlen(input);
	fd = open(data->hd_file_names[index], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		clean_error_exit(data, MSG_ERROR_OPEN, ERROR_OPEN);
	if (write(fd, input, input_len) < input_len)
		clean_error_exit(data, MSG_ERROR_WRITE, ERROR_WRITE);
	try_to_close_fd(data, &fd);
	return (EXIT_SUCCESS);
}

int	run_heredocs(t_minishell *data)
{
	size_t	i;

	i = 0;
	while (i < data->hd_count)
	{
		if (run_heredoc(data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

t_token	*skip_to_heredoc(const t_token *list)
{
	if (!list)
		return (NULL);
	while (list && !is_heredoc(list))
		list = list->next;
	return ((t_token *)list);
}

void	heredoc(t_minishell *data)
{
	if (data->hd_count == 0)
		return ;
	if (data->hd_count > MAX_HEREDOCS)
		clean_error_exit(data, MSG_ERROR_LIMITHEREDOC, ERROR_LIMITHEREDOC);
	if (MAX_HEREDOCS >= 100)
	{
		ft_putendl_fd("Mate, you set the heredoc limit too high, please "
			"reconsider not sabotaging our minishell, thank you.", 2);
		clean_error_exit(data, "Le sigh...", 42);
	}
	create_heredoc_delimiters(data);
	setup_heredoc_file_names(data);
	if (run_heredocs(data) == EXIT_FAILURE)
		clean_error_exit(data, MSG_ERROR_HEREDOC, ERROR_HEREDOC);
}
