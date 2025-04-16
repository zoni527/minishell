/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/09 11:35:04 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_minishell *data)
{
	char	**argv;
	char	**envp;
	t_token	*tokens;
	t_token	*command;

	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
	if (pipe_has_redirections(data))
		if (handle_redirections(data) == EXIT_FAILURE)
			return ;
	tokens = skip_to_pipe_by_index(data);
	command = copy_cmd_and_args_within_pipe(data, tokens);
	argv = create_args_arr(data, command);
	envp = create_envp_arr_from_custom_env(data, data->minishell_env);
	cmd_exec(data, argv, envp);
	ft_putendl_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
}

bool	pipe_has_redirections(const t_minishell *data)
{
	return (pipe_has(data, is_redirection));
}
