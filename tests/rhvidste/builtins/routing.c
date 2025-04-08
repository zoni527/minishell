/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:19:12 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:20:59 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to check wether input is one of the builtins
 *
 * @param input	raw input to parse
 */
int	check_if_builtin(char *input)
{
	if (ft_strncmp("echo", input, 4) == 0)
		return (0);
	if (ft_strncmp("cd", input, 2) == 0)
		return (0);
	if (ft_strncmp("pwd", input, 3) == 0)
		return (0);
	if (ft_strncmp("export", input, 6) == 0)
		return (0);
	if (ft_strncmp("unset", input, 5) == 0)
		return (0);
	if (ft_strncmp("env", input, 3) == 0)
		return (0);
	if (ft_strncmp("exit", input, 4) == 0)
		return (0);
	if (ft_strncmp("getenv", input, 6) == 0)
		return (0);
	return (1);
}

/**
 * Function to reroute to relative built in functions
 *
 * @param data	Main data struct
 * @param str	Input string
 * @param envp	Pointer to envp list
 */
void	reroute_builtin(t_minishell *data, char *str, t_var *envp)
{
	(void)data;
	(void)envp;
	if (ft_strncmp("echo", str, 4) == 0)
//		builtin_echo(str, envp);
		printf("ECHO CALLED");
	if (ft_strncmp("cd", str, 2) == 0)
//		builtin_cd(str, envp);
		printf("CD CALLED\n");
	if (ft_strncmp("pwd", str, 3) == 0)
//		get_current_dir();
		printf("PWD CALLED\n");
	if (ft_strncmp("export", str, 6) == 0)
//		builtin_export(str, envp);
		printf("EXPORT CALLED\n");
	if (ft_strncmp("unset", str, 5) == 0)
//		builtin_unset(str, envp);
		printf("UNSET CALLED\n");
	if (ft_strncmp("env", str, 3) == 0)
//		builtin_env(envp);
		printf("ENV CALLED");
	if (ft_strncmp("exit", str, 4) == 0)
		printf("EXIT CALLED");
	if (ft_strncmp("getenv", str, 6) == 0)
//		ft_getenv(str, envp);
		printf("GETENV CALLED");
}

