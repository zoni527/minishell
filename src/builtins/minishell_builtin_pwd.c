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

/**
 * Prints present working directory by calling get_current_dir, sets
 * data->last_rval to 0;
 *
 * @param data	Pointer to main data struct
 */
void	builtin_pwd(t_minishell *data)
{
	get_current_dir(data);
	data->last_rval = 0;
}
