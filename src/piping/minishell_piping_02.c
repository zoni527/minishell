/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_piping_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:51:37 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/08 09:58:35 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_minishell *data)
{
	char	**argv;

	if (data->pipe_index != 0)
		redirect_stdin_and_close_fd(data, &data->pipe_fds[READ]);
	if (data->pipe_index != data->pipe_count)
		redirect_stdout_and_close_fd(data, &data->pipe_fds[WRITE]);
	if (pipe_has_redirections(data))
		handle_redirections(data);
	if (data->pipe_index == 0)
	{
		char	*argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
	else if (data->pipe_index == 1)
	{
		char	*argv[] = {"cat", NULL};
		execve("/usr/bin/cat", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
	else
	{
		char	*argv[] = {"wc", NULL};
		execve("/usr/bin/wc", argv, (char **)data->initial_env);
		ft_putstr_fd(MSG_ERROR_EXECVE, STDERR_FILENO);
	}
}

bool	pipe_has_redirections(t_minishell *data)
{
	size_t	pipe_index;
	t_token	*token;

	if (!data || !data->token_list)
		return (false);
	pipe_index = data->pipe_index;
	token = data->token_list;
	while (pipe_index)
	{
		while (token->type != PIPE)
			token = token->next;
		token = token->next;
		--pipe_index;
	}
	while (token && token->type != PIPE)
	{
		if (is_redirection(token))
			return (true);
		token = token->next;
	}
	return (false);
}
