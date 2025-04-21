/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_word_lexing_01.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:35 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/12 15:16:14 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_minishell *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell lexing test: ");
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
		if (contains_syntax_error(data->token_list))
			log_syntax_error(syntax_error_at_token(data->token_list));
		print_debug(data);
		data->token_list = NULL;
		free(line);
	}
}

int	main(void)
{
	static t_minishell	data;

	data.minishell_env = &(t_var){.raw = "ARG=|test|", \
		.key = "ARG", .value = "|test|"};
	data.minishell_env->next = &(t_var){.raw = "DERP=|derp|", .key = "DERP", \
		.value = "|derp|"};
	data.minishell_env->next->next = &(t_var){.raw = "X=\"Hello world\"", \
		.key = "X", .value = "\"Hello world\""};
	data.arena = ft_new_memarena();
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
