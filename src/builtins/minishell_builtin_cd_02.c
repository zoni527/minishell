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
 */
static int	handle_tilde(t_minishell *data, char *path)
{
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	new_path = ft_ma_substr(data->arena, path, 1, (ft_strlen(path) - 1));
	home_path = ms_getenv(data, "HOME");
	new_home_path = ft_ma_strjoin(data->arena, home_path, new_path);
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
 */
static int	handle_no_arg(t_minishell *data)
{
	char	*home_path;

	home_path = ms_getenv(data, "HOME");
	if (change_dir(data, home_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ms_setenv(data, "PWD", home_path);
	return (EXIT_SUCCESS);
}

/**
 * Function to handle the DASH case for CD builtin
 *
 * @param data	main data struct
 */
static int	handle_dash(t_minishell *data)
{
	char	*path;

	path = ms_getenv(data, "OLDPWD");
	if (change_dir(data, path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ms_setenv(data, "PWD", path);
	return (EXIT_SUCCESS);
}

/**
 * Function to handle the change_dir case for CD builtin
 *
 * @param data	main data struct
 * @param path	pointer to path
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
