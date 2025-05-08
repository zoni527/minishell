/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:52:11 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/29 15:50:02 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_minishell_error(const char *str, t_error error);
static void	print_preamble(const char *str);
static void	print_error_message(const char *str, const char *msg);

/**
 * Function categorizes errors, calls the correct error messaging function and
 * sets the correct return value by calling match_exit_value_to_error.
 *
 * @param data	Pointer to main data struct
 * @param str	String associated with error, could be a file name or incorrect
 *				command name
 * @param error	Error flag to match
 *
 * @see	match_exit_value_to_error
 */
void	handle_error(t_minishell *data, const char *str, t_error error)
{
	if (errno == ENOMEM)
		clean_error_exit(data, MSG_ERROR_ENOMEM, ERROR_ENOMEM);
	if (match_minishell_error(str, error) == EXIT_FAILURE)
		ms_perror(data, str);
	close_fds(data);
	match_exit_value_to_error(data, error);
}

/**
 * @param str	String associated with error, could be a file name or incorrect
 *				command name
 * @param error	Error flag to match
 *
 * @return	EXIT_SUCCESS if matching error is found, EXIT_FAILURE if not
 */
static int	match_minishell_error(const char *str, t_error error)
{
	if (error == ERROR_NOSUCH)
		print_error_message(str, MSG_ERROR_NOSUCH);
	else if (error == ERROR_NODELIM)
		print_error_message(str, MSG_ERROR_NODELIM);
	else if (error == ERROR_NOCMD)
		print_error_message(str, MSG_ERROR_NOCMD);
	else if (error == ERROR_PERMISSION || error == ERROR_BINPERM)
		print_error_message(str, MSG_ERROR_PERMISSION);
	else if (error == ERROR_ISADIR)
		print_error_message(str, MSG_ERROR_ISADIR);
	else if (error == ERROR_NOTADIR)
		print_error_message(str, MSG_ERROR_NOTADIR);
	else if (error == ERROR_NOHOME)
		print_error_message(str, MSG_ERROR_NOHOME);
	else if (error == ERROR_NOOLDPWD)
		print_error_message(str, MSG_ERROR_NOOLDPWD);
	else if (error == ERROR_TOOLONG)
		print_error_message(NULL, MSG_ERROR_TOOLONG);
	else if (error == ERROR_UNCLOSED)
		print_error_message(str, MSG_ERROR_UNCLOSED);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @param str	String associated with error, could be a file name or incorrect
 *				command name
 * @param msg	Error message that is associated with the previously matched
 *				error
 */
static void	print_error_message(const char *str, const char *msg)
{
	print_preamble(str);
	ft_putendl_fd(msg, STDERR_FILENO);
}

/**
 * Prints the preamble part of error message, aka "<prompt>: <str>: "
 *
 * @param str	String associated with error, could be a file name or incorrect
 *				command name
 */
static void	print_preamble(const char *str)
{
	ft_putstr_fd(STR_PROMPTSTART, STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}
