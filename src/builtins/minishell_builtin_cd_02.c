/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd_02.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:23:32 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/30 13:24:07 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to handle the tilde key case for CD builtin
 *
 * @param data	minishell data struct
 * @param path	path to change dir too.
 * @param envp	pointer to the first element in envp list
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	handle_tilde(t_minishell *data, char *path)
{
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	new_path = ms_substr(data, path, 1, (ft_strlen(path) - 1));
	home_path = ms_getenv(data, "HOME");
	if (home_path == NULL)
	{
		handle_error(data, "cd", ERROR_NOHOME);
		return (EXIT_FAILURE);
	}
	new_home_path = ms_strjoin(data, home_path, new_path);
	if (change_dir(data, new_home_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ms_setenv(data, "PWD", new_home_path);
	return (EXIT_SUCCESS);
}

/**
 * Function to handle the CD case for CD builtin
 *
 * @param data	main data struct
 * @param envp	pointer to first element in envp list
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	handle_no_arg(t_minishell *data)
{
	char	*home_path;

	home_path = ms_getenv(data, "HOME");
	if (home_path == NULL)
	{
		handle_error(data, "cd", ERROR_NOHOME);
		return (EXIT_FAILURE);
	}
	if (change_dir(data, home_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ms_setenv(data, "PWD", home_path);
	return (EXIT_SUCCESS);
}

/**
 * Function to handle the DASH case for CD builtin
 *
 * @param data	main data struct
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	handle_dash(t_minishell *data)
{
	char	*path;

	path = ms_getenv(data, "OLDPWD");
	if (path == NULL)
	{
		handle_error(data, "cd", ERROR_NOOLDPWD);
		return (EXIT_FAILURE);
	}
	if (change_dir(data, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ms_setenv(data, "PWD", path);
	ft_putendl(path);
	return (EXIT_SUCCESS);
}

/**
 * Function to handle the change_dir case for CD builtin
 *
 * @param data	main data struct
 * @param path	pointer to path
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
static int	handle_change_dir(t_minishell *data, char *path)
{
	char	*new_path;

	if (change_dir(data, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_path = safe_getcwd(data);
	ms_setenv(data, "PWD", new_path);
	return (EXIT_SUCCESS);
}

/**
 * @param data		Pointer to main data struct
 * @param cd_tokens	Tokens that contain the command and arguments for cd
 * @param path		Path to change to
 *
 * @return	EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	handle_cd(t_minishell *data, t_token *cd_tokens, char *path)
{
	if (ft_strncmp(data->raw_input, "cd \"\"", 5) == 0
		&& (data->raw_input[6] == ' ' || data->raw_input[6] == '\0'))
		return (EXIT_SUCCESS);
	else if (path != NULL && path[0] == '\0')
		return (EXIT_SUCCESS);
	else if (path != NULL && path[0] == '~')
		return (handle_tilde(data, path));
	else if (cd_tokens->next == NULL || path[0] == '\0')
		return (handle_no_arg(data));
	else if (path != NULL && path[0] == '-' && path[1] == '\0')
		return (handle_dash(data));
	else
		return (handle_change_dir(data, path));
	return (EXIT_SUCCESS);
}
