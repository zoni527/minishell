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

extern volatile sig_atomic_t g_signal;

void	loop(t_minishell *data)
{
	char	*line;

	(void)data;
	while (1)
	{
		line = readline("To exit, write exit and press enter: ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		ft_printf("Signal value is: %d\n", g_signal);
		free(line);
	}
	free (line);
}

int	main(void)
{
	static t_minishell	data;

	data.arena = ft_new_memarena();
	if (!data.arena)
		return (ft_write_error_return_int(MSG_ERROR_ALLOC, ERROR_ALLOC));
	set_and_activate_primary_signal_handler(&data);
	loop(&data);
	clean(&data);
	return (0);
}
