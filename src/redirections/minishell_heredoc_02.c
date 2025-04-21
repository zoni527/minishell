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
 * Function uses readline to build heredoc input which is then returned.
 *
 * @param data		Pointer to main data struct
 * @param delimiter	String that delimits the end of heredoc input
 */
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
		handle_error(data, "warning", ERROR_NODELIM);
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
