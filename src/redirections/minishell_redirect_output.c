/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect_output.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:46:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 16:58:36 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(t_minishell *data, const t_token *token)
{
	const char	*file_name;
	int			fd;

	token = skip_to_output_redirection(token);
	while (token)
	{
		file_name = token->next->value;
		if (validate_outfile(data, file_name) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY);
		if (fd < 0)
		{
			handle_error(data, file_name, ERROR_OPEN);
			return (EXIT_FAILURE);
		}
		redirect_stdout_and_close_fd(data, &fd);
		token = skip_to_output_redirection(token->next);
	}
	return (EXIT_SUCCESS);
}

const t_token	*skip_to_output_redirection(const t_token *list)
{
	if (!list)
		return (NULL);
	while (list && !is_output_redirection(list) && !is_pipe(list))
		list = list->next;
	if (!list || is_pipe(list))
		return (NULL);
	return (list);
}

int	validate_outfile(t_minishell *data, const char *file_name)
{
	if (ft_is_empty_string(file_name))
	{
		handle_error(data, file_name, ERROR_NOSUCH);
		return (EXIT_FAILURE);
	}
	if (is_a_directory(data, file_name) \
		|| pretends_to_be_a_directory(data, file_name))
	{
		handle_error(data, file_name, ERROR_ISADIRECTORY);
		return (EXIT_FAILURE);
	}
	if (access(file_name, W_OK) < 0)
	{
		handle_error(data, file_name, ERROR_PERMISSION);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	contains_output_redirection(const t_token *list)
{
	if (!list)
		return (false);
	while (list && !is_output_redirection(list))
		list = list->next;
	if (list)
		return (true);
	return (false);
}
