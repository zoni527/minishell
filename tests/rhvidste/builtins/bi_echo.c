/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:21:43 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:24:04 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to call the ECHO builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	builtin_echo(char *input, t_var *envp)
{
	(void)envp;
	char	*sub_str;
	char	*n_str;
	char	*no_quotes;
	sub_str = ft_substr(input, 5, ft_strlen(input) - 4);
	if (sub_str[0] == '-' && sub_str[1] == 'n')
	{
		n_str = ft_substr(sub_str, 3, ft_strlen(sub_str) -2);
		no_quotes = remove_quotes(n_str);
		free(n_str);
		ft_putstr_fd(no_quotes, STDOUT_FILENO);
		free(no_quotes);
	}
	else
	{
		no_quotes = remove_quotes(sub_str);
		ft_putendl_fd(no_quotes, STDOUT_FILENO);
		free(no_quotes);
	}
	free(sub_str);
}
