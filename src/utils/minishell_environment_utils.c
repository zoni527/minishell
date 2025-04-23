/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:00:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/22 16:23:19 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to get the length of the
 * envp list
 *
 * @param envp	pointer to the fist envp element
 */
int	get_envp_len(t_var *envp)
{
	if (envp == 0)
		return (0);
	else
		return (1 + get_envp_len(envp->next));
}
