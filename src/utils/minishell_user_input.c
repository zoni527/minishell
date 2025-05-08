/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_user_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:15:18 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/08 14:57:10 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_prompt(t_minishell *data);

/**
 * If the current instance of minishell is a tty readline is used, otherwise
 * get_next_line reads input one line at a time, without giving a prompt.
 *
 * @param data	Pointer to main data struct
 *
 * @return	Int flag for success or failure
 */
int	read_user_input(t_minishell *data)
{
	const char	*prompt;

	if (isatty(STDIN_FILENO))
	{
		prompt = get_prompt(data);
		data->raw_input = readline(prompt);
	}
	else
		data->raw_input = get_next_line(STDIN_FILENO);
	if (!data->raw_input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Fetches current directory and constructs a prompt by string joining the
 * directory with other strings set in minishell.h.
 *
 * @param data	Pointer to main data struct
 * @param envp	NULL terminated array of environment variables
 *
 * @return	Prompt formed from the default start portion, current directory and
 *			the default prompt delimiter
 *
 * @see safe_getcwd
 */
static const char	*get_prompt(t_minishell *data)
{
	const char	*prompt;
	char		*current_dir;

	current_dir = safe_getcwd(data);
	if (!current_dir[0])
		current_dir = ft_ma_strdup(data->arena, "./");
	prompt = ft_ma_strjoin(data->arena, STR_PROMPTSTART, BGRN);
	prompt = ft_ma_strjoin(data->arena, prompt, current_dir);
	prompt = ft_ma_strjoin(data->arena, prompt, CRESET);
	prompt = ft_ma_strjoin(data->arena, prompt, STR_PROMPTDELIM);
	return (prompt);
}
