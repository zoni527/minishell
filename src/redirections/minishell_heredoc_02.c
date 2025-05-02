/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:19:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/17 12:30:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rl_heredoc_signal_handler(void)
{
	if (g_signal == SIGINT)
	{
		ft_putstr("^C");
		rl_done = 1;
	}
	return (EXIT_SUCCESS);
}

static char	*input_loop(t_minishell *data, char **result, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0 || g_signal == SIGINT)
			break ;
		*result = ft_ma_strjoin(data->arena, *result, line);
		*result = ft_ma_strjoin(data->arena, *result, "\n");
		free(line);
	}
	return (line);
}

/**
 * Function uses readline to build heredoc input which is then returned.
 *
 * @param data		Pointer to main data struct
 * @param delimiter	String that delimits the end of heredoc input
 */
char	*read_heredoc_input(t_minishell *data, const char *delimiter)
{
	char	*line;
	char	*result;
	int		std_in;

	rl_event_hook = &rl_heredoc_signal_handler;
	result = "";
	std_in = safe_dup(data, STDOUT_FILENO);
	line = input_loop(data, &result, delimiter);
	safe_dup2(data, std_in, STDIN_FILENO);
	safe_close(data, &std_in);
	rl_event_hook = &rl_signal_handler;
	if (!line && g_signal == 0)
		handle_error(data, "warning", ERROR_NODELIM);
	free(line);
	if (g_signal == SIGINT)
	{
		data->last_rval = 128 + SIGINT;
		g_signal = 0;
		return (NULL);
	}
	return (result);
}

/**
 * Skips to first heredoc in list.
 *
 * @param list	First node in list of tokens
 */
t_token	*skip_to_heredoc(const t_token *list)
{
	return (skip_to(list, is_heredoc));
}
