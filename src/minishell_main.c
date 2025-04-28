/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:05:41 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/24 14:29:02 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			loop(t_minishell *data);
static void			execution(t_minishell *data);
static void			initialize_data(t_minishell *data, char *envp[]);
static const char	*get_prompt(t_minishell *data);

/**
 * @param argc	Argument count from shell
 * @param argv	NULL terminated array of argument strings
 * @param envp	NULL terminated array of environment variables
 */
int	main(int argc, char *argv[], char *envp[])
{
	static t_minishell	data;

	(void)argc;
	(void)argv;
	initialize_data(&data, envp);
	set_default_signal_handling(&data);
	loop(&data);
	clean(&data);
	ft_putendl_fd("exit", STDERR_FILENO);
	return (data.last_rval);
}

/**
 * Loop actions consist of reading user input, validating it, running through
 * and calling the actions requested by the input, resetting the data structure
 * after the action/execution stage, and freeing the raw user input before
 * starting again.
 *
 * @param data	Pointer to main data struct
 */
static void	loop(t_minishell *data)
{
	const char	*prompt;

	while (true)
	{
		prompt = get_prompt(data);
		data->raw_input = readline(prompt);
		if (!data->raw_input)
			break ;
		add_history(data->raw_input);
		if (validate_raw_input(data) == EXIT_FAILURE)
			continue ;
		tokenization(data);
		if (validate_tokens(data) == EXIT_FAILURE)
			continue ;
		heredoc(data);
		execution(data);
		reset_arena_and_pointers(data);
		free((void *)data->raw_input);
	}
}

/**
 * @param data	Pointer to main data struct
 */
static void	execution(t_minishell *data)
{
	if (data->pipe_count == 0 && tokens_contain(data->token_list, is_builtin))
		run_single_builtin(data);
	else
		piping(data);
}

/**
 * @param data	Pointer to main data struct
 * @param envp	NULL terminated array of environment variables
 */
static void	initialize_data(t_minishell *data, char *envp[])
{
	data->arena = ft_new_memarena();
	if (!data->arena)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	data->initial_env = (const char **)envp;
	data->pipe_fds[READ] = -1;
	data->pipe_fds[WRITE] = -1;
	env_list_from_envp(data, data->initial_env);
}

/**
 * @param data	Pointer to main data struct
 * @param envp	NULL terminated array of environment variables
 */
static const char	*get_prompt(t_minishell *data)
{
	const char	*prompt;
	char		*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		if (errno == ENOENT)
		{
			current_dir = ft_strdup("./");
			if (!current_dir)
				clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
		}
		else
			clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	}
	prompt = ft_ma_strjoin(data->arena, "minishell: ", current_dir);
	prompt = ft_ma_strjoin(data->arena, prompt, "$ ");
	free(current_dir);
	return (prompt);
}
