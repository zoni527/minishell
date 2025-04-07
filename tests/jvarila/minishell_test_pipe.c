/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/03 16:51:42 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_minishell *data)
{
	while (1)
	{
		piping(data);
		data->token_list = NULL;
		break ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	static t_minishell	data;

	(void)argc;
	(void)argv;
	(void)envp;
	data.arena = ft_new_memarena();
	data.initial_env = (const char **)envp;
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
