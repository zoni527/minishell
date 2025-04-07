/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_safe_pipe_management.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:44:26 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/07 10:50:15 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_to_pipe(t_minishell *data, int *new_pipe)
{
	if (!new_pipe)
		return ;
	if (pipe(new_pipe) < 0)
		clean_error_exit(data, MSG_ERROR_PIPE, ERROR_PIPE);
}
