/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:09:47 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 17:10:14 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_minishell *data)
{
	if (get_current_dir(data) == EXIT_FAILURE)
	{
		data->last_rval = EXIT_FAILURE;
		return ;
	}
	data->last_rval = EXIT_SUCCESS;
}
