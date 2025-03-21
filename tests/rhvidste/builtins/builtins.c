/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtest00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:27:54 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/12 17:07:02 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	static t_minishell	data;
	char	*input;
	char	*shell_dir;
	char	*buffer;
	char	**envp_arr;

	//first parsing the enviroment variables into a linked list
	parse_env(&data, envp);
	while (1)
	{	
		buffer = getcwd(NULL, 0); // gets the current dir
		shell_dir = ft_strjoin("mini_shell: ", buffer);
		shell_dir = ft_strjoin(shell_dir, "$ ");
		input = readline(shell_dir);
		if (!input)
			return (1);
		//Checking for exit case where "exit"
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			printf("exiting program...\n");
			free(input);
			break ;
		}
		if (check_if_builtin(input) == 0)
		{
			reroute_builtin(&data, input, data.custom_env);
		}
		else
		{
			envp_arr = convert_envp_to_arr(data.custom_env);
			run_prog(input, envp_arr);
		}
		add_history(input);
	}
	free_list(data.custom_env);
	return (0);
}
