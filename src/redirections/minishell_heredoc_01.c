/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:01:54 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/08 14:25:32 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_heredoc_delimiters(t_minishell *data);
static void	setup_heredoc_file_names(t_minishell *data);
static int	run_heredocs(t_minishell *data);
static int	run_heredoc(t_minishell *data, int index);

/**
 * Loops through indices 0 -> data->hd_count - 1, calls run_heredoc for each
 * index.
 *
 * @param data	Pointer to main data struct
 *
 * @return	EXIT_SUCCESS for successful heredoc input collection, EXIT_FAILURE
 *			for failure
 */
int	heredoc(t_minishell *data)
{
	if (data->hd_count == 0)
		return (EXIT_SUCCESS);
	if (data->hd_count > MAX_HEREDOCS)
		clean_error_exit(data, MSG_ERROR_LIMITHEREDOC, EXIT_LIMITHEREDOC);
	if (MAX_HEREDOCS >= 100)
	{
		ft_putendl_fd("Mate, you set the heredoc limit too high, please "
			"reconsider not sabotaging our minishell, thank you.", 2);
		clean_error_exit(data, "Le sigh...", 42);
	}
	create_heredoc_delimiters(data);
	setup_heredoc_file_names(data);
	if (run_heredocs(data) == EXIT_FAILURE)
	{
		free((void *)data->raw_input);
		reset_data(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Creates and assigns values to data->hd_delimiters based on the heredoc count
 * specified by data->hd_count.
 *
 * @param data	Pointer to main data struct
 */
static void	create_heredoc_delimiters(t_minishell *data)
{
	t_token	*token;
	size_t	i;

	data->hd_delimiters = ms_calloc(data, data->hd_count + 1,
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

/**
 * Creates file names for heredoc files. The format is
 * /tmp/minishell_heredoc_[0-9][0-9]. Uses the token's
 * index to create a unique matching file name.
 *
 * @param data	Pointer to main data struct
 */
static void	setup_heredoc_file_names(t_minishell *data)
{
	const t_token	*heredoc;
	const char		*file_name;
	char			*file_index;
	const char		*file_name_base;
	size_t			i;

	data->hd_file_names = ms_calloc(data, data->hd_count + 1,
			sizeof(char *));
	file_name_base = "/tmp/minishell_heredoc_";
	heredoc = skip_to_heredoc(data->token_list);
	file_index = ms_calloc(data, 3, sizeof(char));
	i = 0;
	while (heredoc)
	{
		if (heredoc->index < 10)
			file_index[0] = '0';
		else
			file_index[0] = '0' + heredoc->index / 10;
		file_index[1] = '0' + heredoc->index % 10;
		file_name = ms_strjoin(data, file_name_base, file_index);
		data->hd_file_names[i] = file_name;
		heredoc = skip_to_heredoc(heredoc->next);
		++i;
	}
}

/**
 * Loops through indices 0 -> data->hd_count - 1, calls run_heredoc for each
 * index.
 *
 * @param data	Pointer to main data struct
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	run_heredocs(t_minishell *data)
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

/**
 * Gathers and saves input for the heredoc denoted by index.
 *
 * @param data	Pointer to main data struct
 * @param index	Index for heredoc delimiter and file name selection
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	run_heredoc(t_minishell *data, int index)
{
	const char	*delimiter;
	const char	*input;
	int			fd;
	int			input_len;
	t_token		*temp;

	delimiter = data->hd_delimiters[index];
	input = read_heredoc_input(data, delimiter);
	if (!input)
		return (EXIT_FAILURE);
	temp = new_token_node(data, input);
	deactivate_quotes(temp->value);
	expand_variables(data, temp);
	reactivate_quotes(temp->value);
	input = temp->value;
	input_len = ft_strlen(input);
	fd = open(data->hd_file_names[index], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		clean_error_exit(data, MSG_ERROR_OPEN, ERROR_OPEN);
	if (write(fd, input, input_len) < input_len)
		clean_error_exit(data, MSG_ERROR_WRITE, ERROR_WRITE);
	safe_close(data, &fd);
	return (EXIT_SUCCESS);
}
