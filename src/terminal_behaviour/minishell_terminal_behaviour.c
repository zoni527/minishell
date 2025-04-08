/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal_behaviour.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:52:58 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/31 14:50:39 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean_exit(data, ERROR_TCGETATTR);
//term.c_lflag |= ISIG;
//term.c_cc[VQUIT] = _POSIX_VDISABLE;
// clean_exit(data, ERROR_TCGETATTR);
void	set_terminal(t_minishell *data)
{
	struct termios	term;

	(void)data;
	if (tcgetattr(STDIN_FILENO, &term))
	{
		ft_putendl_fd(MSG_ERROR_TCGETATTR, \
				STDERR_FILENO);
		exit(ERROR_TCGETATTR);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
	{
		ft_putendl_fd(MSG_ERROR_TCSETATTR, \
				STDERR_FILENO);
		exit(ERROR_TCSETATTR);
	}
}
