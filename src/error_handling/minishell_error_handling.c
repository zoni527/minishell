/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:52:11 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 15:55:24 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_minishell *data, const char *str, int error)
{
	if (errno == ENOMEM)
		clean_error_exit(data, MSG_ERROR_ENOMEM, ERROR_ENOMEM);
	close_fds(data);
	data->error = error;
	ms_perror(data, str);
}
