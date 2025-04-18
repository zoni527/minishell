/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect_heredoc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:05:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/18 12:44:42 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_file_name_index(t_minishell *data, const t_token *heredoc);

int	redirect_heredoc(t_minishell *data, const t_token *heredoc)
{
	const char		*file_name;
	size_t			file_name_index;
	int				fd;

	file_name_index = get_file_name_index(data, heredoc);
	file_name = data->hd_file_names[file_name_index];
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		clean_error_exit(data, MSG_ERROR_HEREDOC_FILE, EXIT_HEREDOC_FILE);
	redirect_stdin_and_close_fd(data, &fd);
	if (unlink(file_name) < 0)
		handle_error(data, file_name, ERROR_UNLINK);
	return (EXIT_SUCCESS);
}

static size_t	get_file_name_index(t_minishell *data, const t_token *heredoc)
{
	size_t			file_name_index;
	const t_token	*token;

	file_name_index = 0;
	token = skip_to_heredoc(data->token_list);
	while (token && token->index != heredoc->index)
	{
		++file_name_index;
		token = skip_to_heredoc(token->next);
	}
	return (file_name_index);
}
