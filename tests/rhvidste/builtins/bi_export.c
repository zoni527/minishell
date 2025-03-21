/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:26:38 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:31:02 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to call the EXPORT builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	builtin_export(char *input ,t_var *envp)
{
	char	*raw;
	char	*key;
	char	*value;
	int	i;
	
	raw = ft_substr(input, 7, ft_strlen(input) -7);

	i = 0;
	while (raw[i] != '=')
	{
		i++;
	}
	key = ft_substr(raw, 0, i);
	value = ft_substr(raw, (i + 1), ft_strlen(raw) - (i + 1));
	ft_setenv(key, value, envp);
}

