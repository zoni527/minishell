/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:24:08 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/09 15:16:44 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_minishell *data, const t_token *token)
{
	const char	*file_name;
	int			fd;

	token = skip_to_input_redirection(token);
	while (token)
	{
		file_name = token->next->value;
		if (validate_infile(data, file_name) == EXIT_FAILURE)
			break ;
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			clean_error_exit(data, MSG_ERROR_OPEN, ERROR_OPEN);
		redirect_stdin_and_close_fd(data, &fd);
		token = skip_to_input_redirection(token->next);
	}
}

const t_token	*skip_to_input_redirection(const t_token *list)
{
	if (!list)
		return (NULL);
	while (list && list->type != REDIRECT_INPUT && list->type != PIPE)
		list = list->next;
	if (!list || list->type == PIPE)
		return (NULL);
	return (list);
}

int	validate_infile(t_minishell *data, const char *file_name)
{
	if (access(file_name, F_OK) < 0)
	{
		ms_perror(file_name, MSG_ERROR_NOSUCH);
		data->error = ERROR_NOSUCH;
		return (EXIT_FAILURE);
	}
	if (access(file_name, R_OK) < 0)
	{
		ms_perror(file_name, MSG_ERROR_PERMISSION);
		data->error = ERROR_PERMISSION;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	contains_input_redirection(const t_token *list)
{
	if (!list)
		return (false);
	while (list && list->type != REDIRECT_INPUT)
		list = list->next;
	if (list && list->next->type == FILE_NAME)
		return (true);
	return (false);
}
