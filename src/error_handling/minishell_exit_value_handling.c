/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit_value_handling.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:25:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/29 11:30:18 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function sets data->last_rval based on the sent error.
 *
 * @param data	Pointer to main data struct
 * @param error	Error flag to match against
 */
void	match_exit_value_to_error(t_minishell *data, t_error error)
{
	if (error == 0)
		return ;
	else if (error == ERROR_BINISADIR || error == ERROR_BINPERM
		|| error == ERROR_BINNOTADIR)
		data->last_rval = EXIT_BINPERM;
	else if (error == ERROR_NOCMD)
		data->last_rval = EXIT_NOCMD;
	else if (error == ERROR_LIMITHEREDOC)
		data->last_rval = EXIT_LIMITHEREDOC;
	else
		data->last_rval = EXIT_FAILURE;
}
