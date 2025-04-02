/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_logging.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:56:34 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/02 14:43:03 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Writes error messages to stderr, always starts with 'minishell: '
 * <p>
 * If file or msg is NULL, omit error for that part
 *
 * @param file	Name of file that msg is targeting, can be NULL
 * @param msg	Error message
 */
void	ms_perror(const char *file, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (file)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

/**
 * Writes syntax error about token to stderr.
 *
 * @param token	Pointer to token that causes a syntax error
 */
void	log_syntax_error(t_token *token)
{
	char	*str;

	if (token)
		str = token->value;
	else
		str = "(NULL)";
	ft_putstr_fd("minishell: syntax error near unexpecter token `", \
			STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
