/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_shell.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:20:59 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/25 14:28:20 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to set the current Shell level
 *
 * @param data	pointer to minishell data struct
 */
void	set_shell_lvl(t_minishell *data)
{
	char	*shell_lvl_str;
	int		shell_lvl_int;

	shell_lvl_str = ms_getenv(data, "SHLVL");
	shell_lvl_int = -1;
	if (shell_lvl_str)
		shell_lvl_int = ft_atoi(shell_lvl_str);
	shell_lvl_int++;
	shell_lvl_str = ft_itoa(shell_lvl_int);
	if (!shell_lvl_str)
		clean_error_exit(data, MSG_ERROR_ALLOC, EXIT_ENOMEM);
	ms_setenv(data, "SHLVL", ms_strdup(data, shell_lvl_str));
	free(shell_lvl_str);
}
