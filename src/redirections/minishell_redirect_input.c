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

static const t_token	*skip_to_input_redirection(const t_token *list);
static int				validate_infile(t_minishell *data, \
							const char *file_name);

/**
 * Handles input redirections in list. 
 *
 * @param data	Pointer to main data struct
 * @param token	Token to start redirection operation from
 */
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

/**
 * Returns first token that is an input redirection in list. Won't search in
 * multiple pipes.
 *
 * @param list	First token in a list of tokens to search within
 */
static const t_token	*skip_to_input_redirection(const t_token *list)
{
	if (!list)
		return (NULL);
	while (list && !is_input_redirection(list) && !is_pipe(list))
		list = list->next;
	if (!list || is_pipe(list))
		return (NULL);
	return (list);
}

/**
 * Cheks if file exists and whether it can be written into.
 *
 * @param data		Pointer to main data struct
 * @param file_name	String containing a file name
 */
static int	validate_infile(t_minishell *data, const char *file_name)
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
