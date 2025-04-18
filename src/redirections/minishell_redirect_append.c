/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect_append.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:49:11 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 12:52:23 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_append(t_minishell *data, const t_token *append)
{
	const char	*file_name;
	int			fd;

	file_name = append->next->value;
	if (validate_outfile(data, file_name) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		handle_error(data, file_name, ERROR_OPEN);
		return (EXIT_FAILURE);
	}
	redirect_stdout_and_close_fd(data, &fd);
	return (EXIT_SUCCESS);
}
