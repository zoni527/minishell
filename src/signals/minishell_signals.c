/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:38:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/28 16:29:13 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	signal_handler(int signal_type)
{
	g_signal = signal_type;
}

void	setup_signal_handler(t_minishell *data)
{
	sigemptyset(&data->act.sa_mask);
	sigaddset(&data->act.sa_mask, SIGINT);
	sigaddset(&data->act.sa_mask, SIGQUIT);
	data->act.sa_handler = &signal_handler;
	sigaction(SIGINT, &data->act, NULL);
	sigaction(SIGQUIT, &data->act, NULL);
}
