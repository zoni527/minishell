/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:36:20 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:36:24 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to call the ENV builtin
 *
 * @param env	pinter to envp list
 */
void	builtin_env(t_var *env)
{
	t_var	*current;
	current = env;
	while (current)
	{
		ft_putendl_fd(current->raw, 1);
		current = current->next;
	}
}
