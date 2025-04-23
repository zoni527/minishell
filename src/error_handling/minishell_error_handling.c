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

static void	print_preamble(const char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

static void	print_error_mesage(const char *str, const char *msg)
{
	print_preamble(str);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	handle_error(t_minishell *data, const char *str, int error)
{
	if (errno == ENOMEM)
		clean_error_exit(data, MSG_ERROR_ENOMEM, ERROR_ENOMEM);
	close_fds(data);
	data->error = error;
	if (error == ERROR_NOSUCH)
	{
		print_error_mesage(str, MSG_ERROR_NOSUCH);
		return ;
	}
	else if (error == ERROR_NODELIM)
	{
		print_error_mesage(str, MSG_ERROR_NODELIM);
		return ;
	}
	ms_perror(data, str);
}
