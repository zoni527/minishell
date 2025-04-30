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

/**
 * Global signal variable, declared in minishell.h as:
 * extern volatile int g_signal
 */
volatile int	g_signal = 0;

/**
 * Function activates when SIGINT is received. Sets g_signal to SIGINT, writes
 * a newline to stdout, refreshes readline, clears the internal buffer and
 * redisplays the prompt.
 *
 * @param signal_type	Received signal's int code, should always be SIGINT
 */
static void	main_process_default_handler(int signal_type)
{
	g_signal = signal_type;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * @param signal_type	Received signal's int code, should always be SIGINT
 */
static void	main_process_second_handler(int signal_type)
{
	g_signal = signal_type;
	if (signal_type == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
}

/**
 * Initializes signal handling for SIGINT and SIGQUIT. SIGINT activates
 * signal_handler and SIGQUIT is ignored. Saves the previous actions in
 * variables act_<signal name>_old.
 *
 * @param data	Pointer to main data struct
 */
void	set_and_activate_primary_signal_handler(t_minishell *data)
{
	sigemptyset(&data->act_int.sa_mask);
	sigaddset(&data->act_int.sa_mask, SIGINT);
	data->act_int.sa_handler = &main_process_default_handler;
	sigaction(SIGINT, &data->act_int, &data->act_int_old);
	sigemptyset(&data->act_quit.sa_mask);
	sigaddset(&data->act_quit.sa_mask, SIGQUIT);
	data->act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->act_quit, &data->act_quit_old);
}

void	activate_primary_signal_handler(t_minishell *data)
{
	data->act_int.sa_handler = &main_process_default_handler;
	sigaction(SIGINT, &data->act_int, NULL);
	data->act_quit.sa_handler = &main_process_default_handler;
	sigaction(SIGQUIT, &data->act_quit, NULL);
}

void	activate_secondary_signal_handler(t_minishell *data)
{
	data->act_int.sa_handler = &main_process_second_handler;
	sigaction(SIGINT, &data->act_int, NULL);
	data->act_quit.sa_handler = &main_process_second_handler;
	sigaction(SIGQUIT, &data->act_quit, NULL);
}
