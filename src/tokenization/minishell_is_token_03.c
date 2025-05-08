/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_is_token_03.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:00:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 11:17:00 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if token->type is FILE_NAME.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is FILE_NAME, false if not
 */
bool	is_file_name(const t_token *token)
{
	if (token && token->type == FILE_NAME)
		return (true);
	return (false);
}

/**
 * Checks if token->type is ARGUMENT.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is ARGUMENT, false if not
 */
bool	is_argument(const t_token *token)
{
	if (token && token->type == ARGUMENT)
		return (true);
	return (false);
}

/**
 * Checks if token->type is WORD.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is WORD, false if not
 */
bool	is_word(const t_token *token)
{
	if (token && token->type == WORD)
		return (true);
	return (false);
}

/**
 * Checks if token->type is DELIMITER.
 *
 * @param token	Pointer to token which is checked
 *
 * @return	true if token->type is DELIMITER, false if not
 */
bool	is_delimiter(const t_token *token)
{
	if (token && token->type == DELIMITER)
		return (true);
	return (false);
}
