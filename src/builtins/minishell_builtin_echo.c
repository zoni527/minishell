/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:16:42 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/10 16:17:52 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check all characters
 * for the -n flag are n's
 *
 * @param str	str value to check for n characters
 *
 * @return	true if valid n flag string, false if not
 */
static bool	is_valid_n_str(const char *str)
{
	size_t	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

/**
 * Function to execute ECHO
 * builtin function
 *
 * @param data	main data struct
 */
void	builtin_echo(t_minishell *data)
{
	t_token	*token;
	bool	n_flag;

	data->last_rval = 0;
	token = copy_cmd_and_args_within_pipe(data)->next;
	n_flag = false;
	if (token && is_valid_n_str(token->value))
		n_flag = true;
	while (token && is_valid_n_str(token->value))
		token = token->next;
	while (token && token->next)
	{
		ft_putstr(token->value);
		ft_putstr(" ");
		token = token->next;
	}
	if (token)
		ft_putstr(token->value);
	if (!n_flag)
		ft_putendl("");
}
