/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_builtins.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:06:35 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:35 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_minishell *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell piping test: ");
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			break ;
		}
		if (has_unclosed_quotes(line))
		{
			ft_putendl("Input has unclosed quotes");
			free(line);
			continue ;
		}
		data->raw_input = line;
		tokenization(data);
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
	parse_env(&data, (char **)data.initial_env);
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
