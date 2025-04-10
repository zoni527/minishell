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
 */
bool	is_argument(const t_token *token)
{
	if (token && token->type == ARGUMENT)
		return (true);
	return (false);
}
