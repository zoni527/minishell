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
	char	*line;

	while (1)
	{
		line = readline("minishell redirections test: ");
		add_history(line);
		if (has_unclosed_quotes(line))
		{
			ft_putendl("Input has unclosed quotes");
			free(line);
			continue ;
		}
		data->raw_input = line;
		tokenization(data);
		if (fetch_builtin(data))
			if (builtins(data) == 0)
				break ;
		piping(data);
		data->token_list = NULL;
		free(line);
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
	env_list_from_envp(&data, (char **)data.initial_env);
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data);
	ft_free_memarena(data.arena);
	return (data.last_rval);
}
