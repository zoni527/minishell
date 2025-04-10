/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_perror_testing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:00:17 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/10 17:00:20 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	ft_printf("===== ACCESS TESTING =====\n\n");

	ft_printf("access(\"file_does_not_exist\", F_OK)\n");
	if (access("file_does_not_exist", F_OK))
		perror("file_does_not_exist");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"file_does_not_exist\", R_OK)\n");
	if (access("file_does_not_exist", R_OK))
		perror("file_does_not_exist");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"file_does_not_exist\", W_OK)\n");
	if (access("file_does_not_exist", W_OK))
		perror("file_does_not_exist");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"not_a_folder/\", F_OK)\n");
	if (access("not_a_folder/", F_OK))
		perror("not_a_folder/");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"not_a_folder/\", R_OK)\n");
	if (access("not_a_folder/", R_OK))
		perror("not_a_folder/");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"not_a_folder/\", W_OK)\n");
	if (access("not_a_folder/", W_OK))
		perror("not_a_folder/");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"obj\", F_OK)\n");
	if (access("obj", F_OK))
		perror("obj");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"obj\", R_OK)\n");
	if (access("obj", R_OK))
		perror("obj");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"obj\", W_OK)\n");
	if (access("obj", W_OK))
		perror("obj");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c\", F_OK)\n");
	if (access("minishell_perror_testing.c", F_OK))
		perror("minishell_perror_testing.c");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c\", R_OK)\n");
	if (access("minishell_perror_testing.c", R_OK))
		perror("minishell_perror_testing.c");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c\", W_OK)\n");
	if (access("minishell_perror_testing.c", W_OK))
		perror("minishell_perror_testing.c");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c/\", F_OK)\n");
	if (access("minishell_perror_testing.c/", F_OK))
		perror("minishell_perror_testing.c/");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c/\", R_OK)\n");
	if (access("minishell_perror_testing.c/", R_OK))
		perror("minishell_perror_testing.c/");
	ft_putendl_fd("", STDERR_FILENO);

	ft_printf("access(\"minishell_perror_testing.c/\", W_OK)\n");
	if (access("minishell_perror_testing.c/", W_OK))
		perror("minishell_perror_testing.c/");
	ft_putendl_fd("", STDERR_FILENO);

	return (0);
}
