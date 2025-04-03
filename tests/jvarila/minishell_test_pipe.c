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

void	loop(t_minishell *data, char *envp[])
{
	//char	*line;

	while (1)
	{
		//line = readline("minishell piping test: ");
		//if (ft_strncmp(line, "exit", 5) == 0)
		//{
		//	free(line);
		//	break ;
		//}
		//if (has_unclosed_quotes(line))
		//{
		//	ft_putendl("Input has unclosed quotes");
		//	free(line);
		//	continue ;
		//}
		//data->raw_input = line;
		//tokenization(data);
		piping(data, envp);
		data->token_list = NULL;
		//free(line);
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
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data, envp);
	ft_free_memarena(data.arena);
	return (0);
}
