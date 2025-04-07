/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_safe_fd_management.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:50:42 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/07 10:48:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Attempts to close file descriptor pointed to by fd, sets the value to -1
 * when successful to mark *fd as closed. If close fails performs cleanup and
 * exit of program.
 *
 * @param data	Pointer to main data struct
 * @param fd	Pointer to file descriptor to close
 */
void	try_to_close_fd(t_minishell *data, int *fd)
{
	if (!fd || *fd < 0)
		return ;
	if (close(*fd) < 0)
		clean_error_exit(data, MSG_ERROR_CLOSE, ERROR_CLOSE);
	*fd = -1;
}

/**
 * Attempts to call dup2 on fd1 and fd2, performs cleanup and exits program on
 * failure.
 *
 * @param data	Pointer to main data struct
 * @param fd1	File descriptor to redirect fd2 to
 * @param fd2	File descriptor to be overwritten
 */
void	try_to_dup2(t_minishell *data, int fd1, int fd2)
{
	if (fd1 < 0 || fd2 < 0)
		return ;
	if (dup2(fd1, fd2) < 0)
		clean_error_exit(data, MSG_ERROR_DUP2, ERROR_DUP2);
}

/**
 * Calls safe functions for redirecting input and closing file descriptors.
 *
 * @param data	Pointer to main data struct
 * @param fd	Pointer to file descriptor to close
 */
void	redirect_stdout_and_close_fd(t_minishell *data, int *fd)
{
	if (!fd)
		return ;
	try_to_dup2(data, *fd, STDOUT_FILENO);
	try_to_close_fd(data, fd);
}

/**
 * Calls safe functions for redirecting input and closing file descriptors.
 *
 * @param data	Pointer to main data struct
 * @param fd	Pointer to file descriptor to close
 */
void	redirect_stdin_and_close_fd(t_minishell *data, int *fd)
{
	if (!fd)
		return ;
	try_to_dup2(data, *fd, STDIN_FILENO);
	try_to_close_fd(data, fd);
}
