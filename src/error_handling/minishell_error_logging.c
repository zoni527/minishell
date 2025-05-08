/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_logging.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:56:34 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 16:21:24 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Writes error messages to stderr, always starts with 'minishell: '.
 * Calls system error for more information about errno.
 *
 * @param data	Pointer to main data struct
 * @param file	Name of file associated with error
 */
void	ms_perror(t_minishell *data, const char *file)
{
	char	*str;

	str = BHCYN "mini🐚" CRESET;
	if (file)
		str = ft_ma_strjoin(data->arena, STR_PROMPTSTART, file);
	perror(str);
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
	ft_putstr_fd(STR_PROMPTSTART MSG_ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
