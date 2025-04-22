/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:05:41 by jvarila           #+#    #+#             */
/*   Updated: 2025/04/22 13:52:34 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_data(t_minishell *data, char *envp[])
{
	data->arena = ft_new_memarena();
	if(!data->arena)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	data->initial_env = (const char **)envp;
	env_list_from_envp(data, data->initial_env);
}

const char	*get_prompt(t_minishell *data)
{
	const char	*prompt;
	char		*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		if (errno == ENOENT)
		{
			current_dir = ft_strdup(".");
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

int	validate_raw_input(const t_minishell *data)
{
	if (has_unclosed_quotes(data->raw_input))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->raw_input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(MSG_ERROR_UNCLOSED, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validate_tokens(const t_minishell *data)
{
	if (contains_syntax_error(data->token_list))
	{
		log_syntax_error(syntax_error_at_token(data->token_list));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	execution(t_minishell *data)
{
	if (data->pipe_count == 0 && tokens_contain(data->token_list, is_builtin))
	{
		ft_putendl("Functionality missing: need to run builtin "\
			"without piping");
		return ;
	}
	piping(data);
}

void	loop(t_minishell *data)
{
	const char	*prompt;

	while (true)
	{
		prompt = get_prompt(data);
		data->raw_input = readline(prompt);
		if (!data->raw_input)
			break ;
		if (validate_raw_input(data) == EXIT_FAILURE)
		{
			free((void *)data->raw_input);
			continue ;
		}
		tokenization(data);
		if (validate_tokens(data) == EXIT_FAILURE)
		{
			free((void *)data->raw_input);
			continue ;
		}
		heredoc(data);
		execution(data);
		reset_arena_and_pointers(data);
		free((void *)data->raw_input);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	static t_minishell	data;

	(void)argc;
	(void)argv;
	initialize_data(&data, envp);
	loop(&data);
	clean(&data);
	return (data.last_rval);
}
