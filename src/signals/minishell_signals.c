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
volatile sig_atomic_t	g_signal = 0;

/**
 * Function activates when SIGINT is received. Sets g_signal to SIGINT, writes
 * a newline to stdout, refreshes readline, clears the internal buffer and
 * redisplays the prompt.
 *
 * @param signal_type	Received signal's int code, should always be SIGINT
 */
static void	main_process_signal_handler(int signal_type)
{
	g_signal = signal_type;
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
	data->act_int.sa_handler = &main_process_signal_handler;
	data->act_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &data->act_int, &data->act_int_old);
	sigemptyset(&data->act_quit.sa_mask);
	sigaddset(&data->act_quit.sa_mask, SIGQUIT);
	data->act_quit.sa_handler = SIG_IGN;
	data->act_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &data->act_quit, &data->act_quit_old);
	rl_catch_signals = 0;
}

/**
 * Sets data->act_int.sa_handler and data->act_quit.sa_handler, and activates
 * them by calling sigaction.
 *
 * @param data	Pointer to main data struct
 */
void	activate_primary_signal_handler(t_minishell *data)
{
	data->act_int.sa_handler = &main_process_signal_handler;
	sigaction(SIGINT, &data->act_int, NULL);
	data->act_quit.sa_handler = &main_process_signal_handler;
	sigaction(SIGQUIT, &data->act_quit, NULL);
}

/**
 * Creates and activates a signal handler that will ignore SIGINT and SIGQUIT.
 */
void	ignore_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Default readline signal handler, used as a readline hook.
 *
 * @return	EXIT_SUCCESS
 */
int	rl_signal_handler(void)
{
	if (g_signal == SIGINT)
	{
		ft_putendl("^C");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal = SIGINT_DURING_READLINE;
	}
	return (EXIT_SUCCESS);
}
