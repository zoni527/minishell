/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_single_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:20:02 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/25 19:35:11 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_stdin_and_stdout(t_minishell *data, int *std_in,
									 int *std_out);

/**
 * Handler for executing a single builtin within the main process. Cheks for
 * redirections and heredocs, saves copies of stdin and stdout when necessary,
 * and restores the streams to their original states after execution.
 *
 * @param data	Pointer to main data struct
 */
void	run_single_builtin(t_minishell *data)
{
	int	std_in;
	int	std_out;

	std_in = -1;
	std_out = -1;
	if (pipe_has_input_redirection(data) || pipe_has_heredoc(data))
		std_in = safe_dup(data, STDIN_FILENO);
	if (pipe_has_output_redirection(data) || pipe_has_append(data))
		std_out = safe_dup(data, STDOUT_FILENO);
	if (handle_redirections(data) == EXIT_FAILURE)
	{
		restore_stdin_and_stdout(data, &std_in, &std_out);
		return ;
	}
	builtins(data);
	restore_stdin_and_stdout(data, &std_in, &std_out);
}

static void	restore_stdin_and_stdout(t_minishell *data, int *std_in,
									 int *std_out)
{
	safe_dup2(data, *std_in, STDIN_FILENO);
	safe_dup2(data, *std_out, STDOUT_FILENO);
	safe_close(data, std_in);
	safe_close(data, std_out);
}
