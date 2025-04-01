/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:30:12 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/28 16:30:13 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_minishell *data)
{
	char	*line;

	(void)data;
	while (1)
	{
		line = readline("To exit, write exit and press enter: ");
		if (!line)
			;
		else if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			break ;
		}
		ft_printf("Signal value is: %d\n", g_signal);
		free(line);
	}
}

int	main(void)
{
	static t_minishell	data;

	set_terminal(&data);
	data.arena = ft_new_memarena();
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	setup_signal_handler(&data);
	loop(&data);
	ft_free_memarena(data.arena);
	return (0);
}
