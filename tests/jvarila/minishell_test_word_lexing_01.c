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

int	main(int argc, char *argv[])
{
	static t_minishell	data;

	data.custom_env = &(t_var){.raw = "ARG=|test|", \
		.key = "ARG", .value = "|test|"};
	data.custom_env->next = &(t_var){.raw = "DERP=|derp|", .key = "DERP", \
		.value = "|derp|"};
	if (argc != 2)
		return (ft_write_error_return_int("ERROR: input one argument", 1));
	if (has_unclosed_quotes(argv[1]))
		return (ft_write_error_return_int("ERROR: input has unclosed quotes", \
								ERROR_UNCLOSED));
	data.arena = ft_new_memarena();
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	data.raw_input = argv[1];
	lex_raw_input(&data);
	variable_expansion(&data);
	word_splitting(&data);
	quote_removal(&data);
	print_tokens(&data);
	ft_free_memarena(data.arena);
	return (0);
}
