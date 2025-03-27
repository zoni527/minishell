/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:16:34 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/27 11:23:10 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

/**
 * Function to read to here_doc
 *
 * @param data	minishell data struct
 * @param fd	file descriptor / pipe
 * @param limiter	limiter to exit here_doc loop
 */
static void	read_to_here_doc(t_minishell *data, int *fd, const char *limiter)
{
	while (1)
	{
		close(fd[0]);
		data->here_doc_input = readline("> ");
		if (ft_strncmp(limiter, data->here_doc_input, ft_strlen(limiter)) == 0)			{
//			write(fd[1], data->here_doc_input, ft_strlen(here_doc_input))
			free((void *)data->here_doc_input);
//			exit(1);
			break ;
		}
		write(fd[1], data->here_doc_input, ft_strlen(data->here_doc_input));
		add_history(data->here_doc_input);
		free((void *)data->here_doc_input);
	}
	close(fd[1]);
}

/**
 * Function to rum HERE_DOC process
 *
 * @param data	minishell data struct
 * @param limiter	limiter to exit here_doc loop
 */
int	here_doc(t_minishell *data, const char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1);
	reader = fork();
	if (reader == 0)
	{
		read_to_here_doc(data, fd, limiter);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);

	}
	return (0);
}
