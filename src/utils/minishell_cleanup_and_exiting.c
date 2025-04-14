/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanup_and_exiting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:40:03 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/07 10:05:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees heap memory pointers in data.
 *
 * @param data	Pointer to main data struct
 */
void	free_heap_memory(t_minishell *data)
{
	if (data->raw_input)
		free((void *)data->raw_input);
	ft_free_memarena(data->arena);
}

/**
 * Closes file descriptors in data.
 *
 * @param data	Pointer to main data struct
 */
void	close_fds(t_minishell *data)
{
	if (data->pipe_fds[READ] > 2)
	{
		close(data->pipe_fds[READ]);
		data->pipe_fds[READ] = -1;
	}
	if (data->pipe_fds[WRITE] > 2)
	{
		close(data->pipe_fds[WRITE]);
		data->pipe_fds[WRITE] = -1;
	}
}

/**
 * Frees heap memory and closes file descriptors.
 *
 * @param data	Pointer to main data struct
 */
void	clean(t_minishell *data)
{
	free_heap_memory(data);
	close_fds(data);
}

/**
 * Cleans up system resources from data and exits with exit_code.
 *
 * @param data		Pointer to main data struct
 * @param exit_code	Integer value to call exit with
 */
void	clean_exit(t_minishell *data, int exit_code)
{
	clean(data);
	exit(exit_code);
}

/**
 * Performs cleanup, writes error message and exits with exit_code.
 *
 * @param data		Pointer to main data struct
 * @param msg		String that will be logged to stderr before exiting
 * @param exit_code	Integer value to call exit with
 */
void	clean_error_exit(t_minishell *data, const char *msg, int exit_code)
{
	clean(data);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_code);
}
