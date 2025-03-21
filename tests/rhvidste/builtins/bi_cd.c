/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:24:18 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:25:35 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to call the CD builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	builtin_cd(char *input, t_var *envp)
{
	char	*path;
	char	*old_path;
	char	*new_path;
	char	*home_path;
	char	*new_home_path;

	old_path = getcwd(NULL, 0); // get current path to set as old path before change.
	ft_setenv("OLDPWD", old_path, envp);//set the OLD pwd enviroment variable
	path = ft_substr(input, 3, (ft_strlen(input) - 2));
	if (path[0] == '~')
	{
		new_path = ft_substr(path, 1, (ft_strlen(path) - 1));
		home_path = getenv("HOME");
		new_home_path = ft_strjoin(home_path, new_path);
		change_dir(new_home_path);
		ft_setenv("PWD", new_home_path, envp);
		free(new_home_path);
		free(new_path);
	}
	//Here we check is CD is just added on its own.
	else if (path[0] == '\0')
	{
		home_path = getenv("HOME");
		ft_setenv("PWD", home_path, envp);
		change_dir(home_path);
	}
	else
	{
		change_dir(path);
		new_path = getcwd(NULL, 0);
		ft_setenv("PWD", new_path, envp);
	}
	free(path);
}
