/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:33:51 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:36:09 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to call the UNSET builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first envp list element
 */
void	builtin_unset(char *input, t_var *envp)
{
	(void)envp;
	char	*sub_str;

	sub_str = ft_substr(input, 6, ft_strlen(input) - 6);
	remove_env(sub_str, envp);
}

