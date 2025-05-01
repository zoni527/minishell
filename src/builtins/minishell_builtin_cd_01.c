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
 * Function to call the CD builtin
 *
 * @param data	pointer to the main data struct
 * @param builtin_token	pointer to root builtin token
 * @param envp	pointer to fist element in envp array
 */
void	builtin_cd(t_minishell *data)
{
	char	*path;
	char	*old_path;
	t_token	*cd_tokens;

	cd_tokens = copy_cmd_and_args_within_pipe(data);
	old_path = safe_getcwd(data);
	path = NULL;
	if (cd_tokens->next && cd_tokens->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		data->last_rval = EXIT_FAILURE;
		return ;
	}
	if (cd_tokens->next && cd_tokens->next->type == ARGUMENT)
		path = ft_ma_strdup(data->arena, cd_tokens->next->value);
	if (handle_cd(data, cd_tokens, path) == EXIT_FAILURE)
		return ;
	ms_setenv(data, "OLDPWD", old_path);
	data->last_rval = 0;
}
