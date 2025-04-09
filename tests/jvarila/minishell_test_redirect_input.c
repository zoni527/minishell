/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_redirect_input.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/09 17:38:48 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_minishell *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = readline("minishell redirect input test: ");
		if (!line)
			break ;
		add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (has_unclosed_quotes(line))
		{
			ft_putendl("Input has unclosed quotes");
			continue ;
		}
		data->raw_input = line;
		tokenization(data);
		if (contains_input_redirection(data->token_list))
			redirect_input(data, data->token_list);
		piping(data);
		data->token_list = NULL;
	}
	free(line);
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
	data.initial_env = (const char **)envp;
	env_list_from_envp(&data, (char **)data.initial_env);
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
