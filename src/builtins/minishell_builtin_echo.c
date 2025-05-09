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
 * Helper Function to prepare root token
 * before handing to the main function.
 *
 * @param builtin_token	token reference
 *
 * @return	Next token, NULL if no next token
 */
static t_token	*proccess_token(t_token *token)
{
	if (token->next == NULL)
	{
		ft_putendl("");
		return (NULL);
	}
	else
	{
		token = token->next;
		return (token);
	}
	return (NULL);
}

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
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

/**
 * Function to check if token list
 * contains the -n flag for ECHO
 *
 * @param data	main data struct
 *
 * @return	true if valid n flag string, false if not
 */
static bool	is_n(t_minishell *data)
{
	t_token	*token;

	token = copy_tokens_within_pipe(data);
	while (token)
	{
		if (ft_strncmp(token->value, "-n", 2) == 0)
			if (is_valid_n_str(token->value) == true)
				if (token->prev && token->prev->type == BUILTIN)
					return (true);
		token = token->next;
	}
	return (false);
}

/**
 * Helper function to print token to fd
 * or add a new line if at the last argument
 *
 * @param builtin_token	root builtin token reference
 *
 * @return	Flag for builtin_echo to break or keep going
 */
static int	print_token(t_minishell *data, t_token *token)
{
	if (token->prev->type == BUILTIN
		&& token->next == NULL
		&& is_n(data) == true)
		return (0);
	if (token->next && is_n(data) == true)
	{
		ft_putstr(token->next->value);
		if (token->next->next != NULL)
			ft_putstr(" ");
	}
	if (token->type == ARGUMENT && is_n(data) == false)
	{
		ft_putstr(token->value);
		if (token->next && token->next->type == ARGUMENT)
			ft_putstr(" ");
	}
	if (token->next == NULL && is_n(data) == false)
	{
		ft_putstr("\n");
		return (0);
	}
	return (1);
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

	token = copy_cmd_and_args_within_pipe(data);
	token = proccess_token(token);
	if (token == NULL)
		return ;
	while (token)
	{
		if (print_token(data, token) == 0)
			break ;
		token = token->next;
	}
	data->last_rval = 0;
}
