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

/**
 * When sigint is received interrupts readline by setting rl_done to 1.
 *
 * @return	EXIT_SUCCESS
 */
static int	rl_heredoc_signal_handler(void)
{
	if (g_signal == SIGINT)
	{
		ft_putstr("^C");
		rl_done = 1;
	}
	return (EXIT_SUCCESS);
}

/**
 * Builds heredoc input in string pointed by result, one line at a time. Stops
 * when ctrl-D is pressed, SIGINT is received or the delimiter is submitted.
 *
 * @param data		Pointer to main data struct
 * @param result	Pointer to string where heredoc input is saved
 * @param delim		String that contains heredoc delimiter
 *
 * @return	Last line returned by readline
 */
static char	*input_loop(t_minishell *data, char **result, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0 || g_signal == SIGINT)
			break ;
		*result = ms_strjoin(data, *result, line);
		*result = ms_strjoin(data, *result, "\n");
		free(line);
	}
	return (line);
}

/**
 * Activates heredoc specific signal handler for the duration of heredoc input
 * gathering, reactivates default signal handler afterwards.
 *
 * If heredoc is interrupted by ctrl-D calls error handling function, but lets
 * execution continue. Signal interruptions are a cause to stop execution,
 * this is communicated up the chain by returning NULL.
 *
 * @param data		Pointer to main data struct
 * @param delimiter	String that contains heredoc delimiter
 *
 * @return	Heredoc input on success, NULL on signal interrupt
 */
char	*read_heredoc_input(t_minishell *data, const char *delimiter)
{
	char	*line;
	char	*result;

	rl_event_hook = &rl_heredoc_signal_handler;
	result = "";
	line = input_loop(data, &result, delimiter);
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
