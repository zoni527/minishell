/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:09:56 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/28 15:54:56 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* =============================== HEADERS ================================== */

/* -------------------------------------------------------------------- libft */

# include "libft.h"

/* -------------------------------------------- minishell specific inclusions */

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <term.h>

/* =============================== MACROS =================================== */

/* -------------------------------------------------------- numeric constants */

// Default size is 10 MiB (1024^2)
# define MEM_ARENA_SIZE	1048576

/* -------------------------------------------------------------- error codes */

/* Execution errors */
# define ERROR_PERMISSION	1
# define ERROR_BINPERM		126
# define ERROR_NOTFOUND		127

/* Function/system resource errors */
// libft.h: ERROR_ALLOC		2
// libft.h: ERROR_CAPACITY	3
# define ERROR_PIPE			4
# define ERROR_FORK			5
# define ERROR_DUP2			6
# define ERROR_OPEN			7
# define ERROR_CLOSE		8
# define ERROR_EXEC			9
# define ERROR_ACCESS		10
# define ERROR_NOPATH		11
# define ERROR_INPUT		12
# define ERROR_UNLINK		13
# define ERROR_UNCLOSED		14
# define ERROR_TCGETATTR	15
# define ERROR_TCSETATTR	16

/* ---------------------------------------------------------- string literals */

# define STR_MINISHELL			"minishell: "

/* ----------------------------------------------------------- error messages */

# define MSG_ERROR_ALLOC		"ERROR: couldn't alloc"
# define MSG_ERROR_CAPACITY		"ERROR: requested memory chunk is too large"
# define MSG_ERROR_TCGETATTR	"ERROR: failed to get terminal attributes"
# define MSG_ERROR_TCSETATTR	"ERROR: failed to set terminal attributes"
# define MSG_ERROR_CLOSE		"ERROR: failed to close file"
# define MSG_ERROR_PIPE			"ERROR: failed to pipe"
# define MSG_ERROR_FORK			"ERROR: failed to fork"
# define MSG_ERROR_DUP2			"ERROR: failed to dup2"
# define MSG_ERROR_EXECVE		"ERROR: made it past execve"
# define MSG_ERROR_SYNTAX		"syntax error near unexpected token `"

# define METACHARACTERS			"|<> \t\n"

# ifndef READ
#  define READ	0
# endif

# ifndef WRITE
#  define WRITE	1
# endif

/* ================================ ENUMS =================================== */

typedef enum e_token_type
{
	WORD,
	COMMAND,
	ARGUMENT,
	BUILTIN,
	FILE_NAME,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	APPEND
}	t_token_type;

typedef enum e_bltn_type
{
	BLTN_ECHO,
	BLTN_CD,
	BLTN_PWD,
	BLTN_EXPORT,
	BLTN_UNSET,
	BLTN_ENV,
	BLTN_EXIT,
}	t_bltn_type;

/* ================================ TYPEDEFS ================================ */

typedef struct s_token		t_token;
typedef struct s_var		t_var;

typedef struct s_minishell
{
	t_memarena			*arena;
	t_var				*minishell_env;
	t_token				*token_list;
	size_t				token_count;
	size_t				pipe_count;
	size_t				pipe_index;
	int					last_rval;
	int					pipe_fds[2];
	int					final_fd_out;
	int					final_ft_in;
	struct sigaction	act_int;
	struct sigaction	act_int_old;
	struct sigaction	act_quit;
	struct sigaction	act_quit_old;
	const char			*raw_input;
	const char			**initial_env;
}	t_minishell;

typedef struct s_var
{
	char	*raw;
	char	*key;
	char	*value;
	t_var	*next;
	t_var	*prev;
}	t_var;

typedef struct s_token
{
	t_token_type	type;
	size_t			index;
	t_token			*next;
	t_token			*prev;
	char			*value;
}	t_token;

/* =========================== EXTERNAL VARIABLES =========================== */

extern volatile int\
		g_signal;

/* ============================ INPUT VALIDATION ============================ */

/* --------------------------------------------- minishell_quote_validation.c */

bool		has_unclosed_quotes(const char *str);

/* ============================== TOKENIZATION ============================== */

/* ------------------------------------------------- minishell_tokenization.c */

void		tokenization(t_minishell *data);

/* ------------------------------------------- minishell_variable_expansion.c */

void		variable_expansion(t_minishell *data);

/* ----------------------------------------------- minishell_word_splitting.c */

void		word_splitting(t_minishell *data);

/* ------------------------------------------------ minishell_quote_removal.c */

void		quote_removal(t_minishell *data);

/* ------------------------ Classification and ids -------------------------- */

/* ----------------------------------------- minishell_token_classification.c */

void		token_classification(t_minishell *data);

/* -------------------------------------------------- minishell_is_token_01.c */

bool		is_operator(t_token *token);
bool		is_pipe(t_token *token);
bool		is_redirection(t_token *token);
bool		is_input_redirection(t_token *token);
bool		is_output_redirection(t_token *token);

/* -------------------------------------------------- minishell_is_token_02.c */

bool		is_append(t_token *token);
bool		is_heredoc(t_token *token);
bool		is_builtin_or_command(t_token *token);
bool		is_builtin(t_token *token);

/* ----------------------------------------- minishell_assign_token_indices.c */

void		assign_token_indices(t_minishell *data);

/* ------------------------------------------------ minishell_token_getters.c */

t_bltn_type	get_builtin_type(t_token *token);
const char	*get_token_type_str(t_token *token);
t_token		*get_token_by_index(t_token *list, int index);

/* ----------------------------------------------- minishell_token_analysis.c */

size_t		count_tokens(t_token *list);
size_t		count_pipes(t_token *list);

/* ---------------------------------------- minishell_tokenization_utils_01.c */

void		toggle_quote_flag(char *quote_flag, char c);
void		print_tokens(t_minishell *data);
t_token		*new_token_node(t_memarena *arena, const char *str);
void		append_token(t_token **list, t_token *token);
void		insert_token_left(t_token *current, t_token *new);

/* =============================== ENVIRONMENT ============================== */

/* -------------------------------------------------- minishell_environment.c */

void		env_list_from_envp(t_minishell *data, char **envp);
char		**create_envp_arr_from_custom_env(t_minishell *data, \
									t_var *envp_list);
char		*ms_getenv(t_minishell *data, const char *name, t_var *envp);
int			ms_setenv(t_minishell *data, char *key, char *value, t_var *envp);
int			remove_env(char *key, t_var *envp);

/* --------------------------------------------- minishell_environment_list.c */

int			get_env_list_size(t_var *begin);
void		print_env_list(t_var *list);
t_var		*create_new_env_var(t_minishell *data, \
						char *raw, char *key, char *value);

/* ================================ BUILTINS ================================ */

/* ---------------------------------------------- minishell_builtin_handler.c */

t_token		*fetch_builtin(t_minishell *data);
int			builtins(t_minishell *data);

/* ------------------------------------------------- minishell_builtin_echo.c */

void		builtin_echo(t_minishell *data, t_token *builtin_token);

/* --------------------------------------------------- minishell_builtin_cd.c */

int			get_current_dir(t_minishell *data);
int			change_dir(t_minishell *data, char *str);
void		builtin_cd(t_minishell *data, t_token *builtin_token, t_var *envp);

/* -------------------------------------------------- minishell_builtin_pwd.c */

void		builtin_pwd(t_minishell *data);

/* ----------------------------------------------- minishell_builtin_export.c */

void		builtin_export(t_minishell *data, \
					t_token *builtin_token, t_var *envp);

/* ------------------------------------------------ minishell_builtin_unset.c */

void		builtin_unset(t_minishell *data, \
				t_token *builtin_token, t_var *envp);

/* -------------------------------------------------- minishell_builtin_env.c */

void		builtin_env(t_minishell *data);

/* ------------------------------------------------- minishell_builtin_exit.c */

void		builtin_exit(t_minishell *data, t_token *builtin_token);

/* ================================= PIPING ================================= */

/* ---------------------------------------------------- minishell_piping_01.c */

void		piping(t_minishell *data);

/* ---------------------------------------------------- minishell_piping_02.c */

void		child_process(t_minishell *data);
bool		pipe_has_redirections(t_minishell *data);

/* ================================= SIGNALS ================================ */

/* ------------------------------------------------------ minishell_signals.c */

void		set_default_signal_handling(t_minishell *data);
void		activate_sigquit(t_minishell *data);
void		deactivate_sigquit(t_minishell *data);

/* ============================== REDIRECTIONS ============================== */

/* ---------------------------------------------- minishell_redirections_01.c */

void		handle_redirections(t_minishell *data);

/* ------------------------------------------------------ minishell_heredoc.c */

void		heredoc(t_minishell *data);
bool		contains_heredoc(t_token *list);

/* =============================== EXECUTION ================================ */

/* ------------------------------------------------ minishell_execution.c */

char		**create_args_arr(t_minishell *data, t_token *command);
void		cmd_exec(t_minishell *data, char **command, char **envp);

/* ================================= ERRORS ================================= */

/* ------------------------------------------------ minishell_error_logging.c */

void		ms_perror(const char *file, const char *msg);
void		log_syntax_error(t_token *token);

/* ------------------------------------------------- minishell_syntax_error.c */

bool		contains_syntax_error(t_token *list);
t_token		*syntax_error_at_token(t_token *list);

/* ================================== UTILS ================================= */

/* ------------------------------------------------- minishell_var_name_len.c */

size_t		var_name_len(const char *str);

/* -------------------------------------------------- minishell_print_debug.c */

void		print_debug_tokens(t_token *list);
void		print_debug(t_minishell *data);

/* ------------------------------------------ minishell_cleanup_and_exiting.c */

void		free_heap_memory(t_minishell *data);
void		close_fds(t_minishell *data);
void		clean(t_minishell *data);
void		clean_exit(t_minishell *data, int exit_code);
void		clean_error_exit(t_minishell *data, const char *msg, int exit_code);

/* ------------------------------------------- minishell_safe_fd_management.c */

void		try_to_close_fd(t_minishell *data, int *fd);
void		try_to_dup2(t_minishell *data, int fd1, int fd2);
void		redirect_stdout_and_close_fd(t_minishell *data, int *fd);
void		redirect_stdin_and_close_fd(t_minishell *data, int *fd);

/* ----------------------------------------- minishell_safe_pipe_management.c */

void		try_to_pipe(t_minishell *data, int *new_pipe);

/* -------------------------------------------------------------------------- */

void		set_terminal(t_minishell *data);
void		execution(t_minishell *data);

#endif
