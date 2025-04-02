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
void	signal_handler(int signal_type)
{
	g_signal = signal_type;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * Initializes signal handling for SIGINT and SIGQUIT. SIGINT activates
 * signal_handler and SIGQUIT is ignored. Saves the previous actions in
 * variables act_<signal name>_old.
 *
 * @param data	Pointer to main data struct
 */
void	set_default_signal_handling(t_minishell *data)
{
	sigemptyset(&data->act_int.sa_mask);
	sigaddset(&data->act_int.sa_mask, SIGINT);
	data->act_int.sa_handler = &signal_handler;
	sigaction(SIGINT, &data->act_int, &data->act_int_old);
	sigemptyset(&data->act_quit.sa_mask);
	sigaddset(&data->act_quit.sa_mask, SIGQUIT);
	data->act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->act_quit, &data->act_quit_old);
}

/**
 * Changes the signal handler for SIGQUIT to the original one, reactivating
 * the signal (can cause core dumps again).
 *
 * @param data	Pointer to main data struct
 */
void	activate_sigquit(t_minishell *data)
{
	sigaction(SIGQUIT, &data->act_quit_old, NULL);
}

/**
 * Deactivates the signal handler for SIGQUIT, replaces it with SIG_IGN.
 *
 * @param data	Pointer to main data struct
 */
void	deactivate_sigquit(t_minishell *data)
{
	sigaction(SIGQUIT, &data->act_quit, NULL);
}
