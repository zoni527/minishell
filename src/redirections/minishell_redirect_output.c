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

/**
 * Handles output redirections in list. 
 *
 * @param data	Pointer to main data struct
 * @param token	Token to start redirection operation from
 */
int	redirect_output(t_minishell *data, const t_token *output)
{
	const char	*file_name;
	int			fd;

	file_name = output->next->value;
	if (validate_outfile(data, file_name) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		handle_error(data, file_name, ERROR_OPEN);
		return (EXIT_FAILURE);
	}
	redirect_stdout_and_close_fd(data, &fd);
	return (EXIT_SUCCESS);
}

/**
 * Cheks if file_name is an empty string, or if it is or pretends to be a
 * directory.
 *
 * @param data		Pointer to main data struct
 * @param file_name	String containing a file name
 */
int	validate_outfile(t_minishell *data, const char *file_name)
{
	if (ft_is_empty_string(file_name))
	{
		handle_error(data, file_name, ERROR_NOSUCH);
		return (EXIT_FAILURE);
	}
	if (is_a_directory(data, file_name)
		|| pretends_to_be_a_directory(data, file_name))
	{
		handle_error(data, file_name, ERROR_ISADIR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
