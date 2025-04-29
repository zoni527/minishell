/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:11:23 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/08 17:10:17 by rhvidste         ###   ########.fr       */
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
static void	handle_tilde(t_minishell *data, char *path)
{
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	new_path = ft_ma_substr(data->arena, path, 1, (ft_strlen(path) - 1));
	home_path = ms_getenv(data, "HOME");
	new_home_path = ft_ma_strjoin(data->arena, home_path, new_path);
	change_dir(data, new_home_path);
	ms_setenv(data, "PWD", new_home_path);
}

/**
 * Function to handle the CD case for CD builtin
 *
 * @param data	main data struct
 * @param envp	pointer to first element in envp list
 */
static void	handle_cd(t_minishell *data)
{
	char	*home_path;

	home_path = ms_getenv(data, "HOME");
	ms_setenv(data, "PWD", home_path);
	change_dir(data, home_path);
}

/**
 * Function to handle the DASH case for CD builtini
 *
 * @param data	main data struct
 */
static void	handle_dash(t_minishell *data)
{
	char	*path;

	path = ms_getenv(data, "OLDPWD");
	change_dir(data, path);
	ms_setenv(data, "PWD", path);
}

/**
 * Function to handle the change_dir case for CD builtin
 *
 * @param data	main data struct
 * @param path	pointer to path
 */
static void	handle_change_dir(t_minishell *data, char *path)
{
	char	*new_path;

	change_dir(data, path);
	new_path = safe_getcwd(data);
	ms_setenv(data, "PWD", new_path);
	free(new_path);
}

/**
 * Function to call the CD builtin
 *
 * @param data	pointer to the main data struct
 * @param builtin_token	pointer to root builtin token
 * @param envp	pointer to fist element in envp array
 */
void	builtin_cd(t_minishell *data, t_token *builtin_token)
{
	char	*path;
	char	*old_path;

	path = NULL;
	old_path = safe_getcwd(data);
	if (builtin_token->next && builtin_token->next->type == ARGUMENT)
		path = ft_ma_strdup(data->arena, builtin_token->next->value);
	if (path != NULL && !(path[0] == '-' && path[1] == '\0'))
		ms_setenv(data, "OLDPWD", old_path);
	free(old_path);
	if (builtin_token && builtin_token->next && builtin_token->next->next)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (ft_strncmp(data->raw_input, "cd \"\"", 5) == 0
		&& (data->raw_input[6] == ' ' || data->raw_input[6] == '\0'))
		return ;
	else if (path != NULL && path[0] == '~')
		handle_tilde(data, path);
	else if (builtin_token->next == NULL || path[0] == '\0')
		handle_cd(data);
	else if (path != NULL && path[0] == '-' && path[1] == '\0')
		handle_dash(data);
	else
		handle_change_dir(data, path);
}
