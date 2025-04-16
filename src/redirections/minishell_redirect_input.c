/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:24:08 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 16:07:26 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_minishell *data, const t_token *token)
{
	const char	*file_name;
	int			fd;

	token = skip_to_input_redirection(token);
	while (token)
	{
		file_name = token->next->value;
		if (validate_infile(data, file_name) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
		{
			handle_error(data, file_name, ERROR_OPEN);
			return (EXIT_FAILURE);
		}
		redirect_stdin_and_close_fd(data, &fd);
		token = skip_to_input_redirection(token->next);
	}
	return (EXIT_SUCCESS);
}

const t_token	*skip_to_input_redirection(const t_token *list)
{
	if (!list)
		return (NULL);
	while (list && !is_input_redirection(list) && !is_pipe(list))
		list = list->next;
	if (!list || is_pipe(list))
		return (NULL);
	return (list);
}

int	validate_infile(t_minishell *data, const char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		handle_error(data, file_name, ERROR_NOSUCH);
		return (EXIT_FAILURE);
	}
	if (access(file_name, R_OK) < 0)
	{
		handle_error(data, file_name, ERROR_PERMISSION);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	contains_input_redirection(const t_token *list)
{
	return (tokens_contain(list, is_input_redirection));
}
