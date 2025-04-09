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
	if (!list)
		return (false);
	while (list && list->type != HEREDOC)
		list = list->next;
	if (list && list->next && list->next->type == ARGUMENT)
		return (true);
	return (false);
}

t_token	*skip_to_heredoc(t_token *list)
{
	if (!list)
		return (NULL);
	while (list && list->type != HEREDOC)
		list = list->next;
	return (list);
}

void	heredoc(t_minishell *data)
{
	char	*delimiter;
	char	*result;
	t_token	*token;
	char	*line;

	result = "";
	token = skip_to_heredoc(data->token_list);
	delimiter = token->next->value;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		result = ft_ma_strjoin(data->arena, result, line);
		result = ft_ma_strjoin(data->arena, result, "\n");
		free(line);
	}
	ft_putstr(result);
}
