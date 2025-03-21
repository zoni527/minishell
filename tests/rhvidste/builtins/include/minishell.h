/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:54:02 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/14 15:04:05 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/* ============================== TYPEDEFS ===================================*/

typedef struct s_var	t_var;

typedef struct s_var 
{
	char	*raw;
	char	*key;
	char	*value;
	t_var	*next;
	t_var	*prev;
}	t_var;

typedef struct s_minishell 
{
	t_var		*custom_env;
//	const char	*initial_env[];
}	t_minishell;


/* ============================== DEFINITIONS ===================================*/
// UTILS
int	free_array(char **arr);
char	*remove_quotes(char *str);
// EXECUTION
char	*set_paths(char *command, char **mypaths);
char	*path_parsing(char *command, char **envp);
void	cmd_exec(char *argv, char **envp);
int		run_prog(char *input, char **envp);
// DIR
int		get_current_dir(void);
int		change_dir(char *str);
// ENVIROMENT
void	parse_env(t_minishell *data, char **envp);
char	**convert_envp_to_arr(t_var *envp_list);
char	*ft_getenv(const char *name, t_var *envp);
int		ft_setenv(char *key, char *value, t_var *envp);
int		remove_env(char *key, t_var *envp);
// LIST
int		get_list_size(t_var *begin_list);
void	free_list(t_var *head);
void	print_env_list(t_var *list);
t_var	*append_node(t_var *prev, char *raw, char *key, char *value);
// ROUTING
int		check_if_builtin(char *input);
void	reroute_builtin(t_minishell *data, char *str, t_var *envp);
/* ============================== BUILT INS ===================================*/
// ECHO
void	builtin_echo(char *input, t_var *envp);
// CD
void	builtin_cd(char *input, t_var *envp);
// EXPORT
void	builtin_export(char *input ,t_var *envp);
// UNSET
void	builtin_unset(char *input, t_var *envp);
// ENV
void	builtin_env(t_var *env);

# endif
