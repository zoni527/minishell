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
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <term.h>

/* =============================== MACROS =================================== */

/* -------------------------------------------------------- numeric constants */

// Default size is 10 MiB (1024^2)
# define MEM_ARENA_SIZE	1048576

# define MAX_HEREDOCS	16

/* -------------------------------------------------------------- error codes */

/* Execution errors */
# define ERROR_PERMISSION	1
# define ERROR_NOSUCH		1
# define ERROR_ISADIRECTORY	1
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
# define ERROR_ENOMEM		17

/* ---------------------------------------------------------- string literals */

# define STR_MINISHELL			"minishell: "

/* ----------------------------------------------------------- error messages */

# define MSG_ERROR_ALLOC		"ERROR: couldn't alloc"
# define MSG_ERROR_CAPACITY		"ERROR: requested memory chunk is too large"
# define MSG_ERROR_TCGETATTR	"ERROR: failed to get terminal attributes"
# define MSG_ERROR_TCSETATTR	"ERROR: failed to set terminal attributes"
# define MSG_ERROR_OPEN			"ERROR: failed to open"
# define MSG_ERROR_CLOSE		"ERROR: failed to close"
# define MSG_ERROR_PIPE			"ERROR: failed to pipe"
# define MSG_ERROR_FORK			"ERROR: failed to fork"
# define MSG_ERROR_DUP2			"ERROR: failed to dup2"
# define MSG_ERROR_EXECVE		"ERROR: made it past execve"
# define MSG_ERROR_ENOMEM		"ERROR: system is out of memory"
# define MSG_ERROR_SYNTAX		"syntax error near unexpected token `"
# define MSG_ERROR_NOSUCH		"No such file or directory"
# define MSG_ERROR_TOOMANYARGS	"too many arguments"
# define MSG_ERROR_PERMISSION	"Permission denied"
# define MSG_ERROR_ISADIRECTORY	"Is a directory"

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
	int					*heredoc_fds;
	int					final_fd_out;
	int					final_ft_in;
	int					error;
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

bool			has_unclosed_quotes(const char *str);

/* ============================== TOKENIZATION ============================== */

/* ------------------------------------------------- minishell_tokenization.c */

void			tokenization(t_minishell *data);

/* ------------------------------------------- minishell_variable_expansion.c */

void			variable_expansion(t_minishell *data);

/* ----------------------------------------------- minishell_word_splitting.c */

void			word_splitting(t_minishell *data);

/* ------------------------------------------------ minishell_quote_removal.c */

void			quote_removal(t_minishell *data);

/* ------------------------ Classification and ids -------------------------- */

/* ----------------------------------------- minishell_token_classification.c */

void			token_classification(t_minishell *data);

/* -------------------------------------------------- minishell_is_token_01.c */

bool			is_operator(const t_token *token);
bool			is_pipe(const t_token *token);
bool			is_redirection(const t_token *token);
bool			is_input_redirection(const t_token *token);
bool			is_output_redirection(const t_token *token);

/* -------------------------------------------------- minishell_is_token_02.c */

bool			is_append(const t_token *token);
bool			is_heredoc(const t_token *token);
bool			is_builtin_or_command(const t_token *token);
bool			is_builtin(const t_token *token);
bool			is_command(const t_token *token);

/* -------------------------------------------------- minishell_is_token_03.c */

bool			is_file_name(const t_token *token);
bool			is_argument(const t_token *token);

/* ----------------------------------------- minishell_assign_token_indices.c */

void			assign_token_indices(t_minishell *data);

/* ------------------------------------------------ minishell_token_getters.c */

t_bltn_type		get_builtin_type(t_token *token);
const char		*get_token_type_str(t_token *token);
t_token			*get_token_by_index(t_token *list, int index);

/* ----------------------------------------------- minishell_token_analysis.c */

size_t			count_tokens(t_token *list);
size_t			count_pipes(t_token *list);

/* ---------------------------------------- minishell_tokenization_utils_01.c */

void			toggle_quote_flag(char *quote_flag, char c);
void			print_tokens(t_minishell *data);
t_token			*new_token_node(t_memarena *arena, const char *str);
void			append_token(t_token **list, t_token *token);
void			insert_token_left(t_token *current, t_token *new);

/* =============================== ENVIRONMENT ============================== */

/* -------------------------------------------------- minishell_environment.c */

void			env_list_from_envp(t_minishell *data, char **envp);
char			**create_envp_arr_from_custom_env(t_minishell *data, \
										t_var *envp_list);
char			*ms_getenv(t_minishell *data, const char *name, t_var *envp);
int				ms_setenv(t_minishell *data, char *key, char *value, \
				t_var *envp);
int				remove_env(char *key, t_var *envp);

/* ---------------------------------------------- minishell_enviroment_list.c */

int				get_env_list_size(t_var *begin);
void			print_custom_env(t_var *list);
t_var			*create_new_env_var(t_minishell *data, \
						char *raw, char *key, char *value);

/* ================================= PIPING ================================= */

/* ---------------------------------------------------- minishell_piping_01.c */

void			piping(t_minishell *data);

/* ---------------------------------------------------- minishell_piping_02.c */

void			child_process(t_minishell *data);
bool			pipe_has_redirections(const t_minishell *data);

/* ================================= SIGNALS ================================ */

/* ------------------------------------------------------ minishell_signals.c */

void			set_default_signal_handling(t_minishell *data);
void			activate_sigquit(t_minishell *data);
void			deactivate_sigquit(t_minishell *data);

/* ============================== REDIRECTIONS ============================== */

/* ------------------------------------------------- minishell_redirections.c */

int				handle_redirections(t_minishell *data);

/* ----------------------------------------------- minishell_redirect_input.c */

int				redirect_input(t_minishell *data, const t_token *token);
const t_token	*skip_to_input_redirection(const t_token *list);
int				validate_infile(t_minishell *data, const char *file_name);
bool			contains_input_redirection(const t_token *list);

/* ---------------------------------------------- minishell_redirect_output.c */

int				redirect_output(t_minishell *data, const t_token *token);
const t_token	*skip_to_output_redirection(const t_token *list);
int				validate_outfile(t_minishell *data, const char *file_name);
bool			contains_output_redirection(const t_token *list);

/* ------------------------------------------------------ minishell_heredoc.c */

void			heredoc(t_minishell *data);
bool			contains_heredoc(t_token *list);

/* =============================== EXECUTION ================================ */

/* ---------------------------------------------------- minishell_execution.c */

char			**create_args_arr(t_minishell *data, t_token *command);
void			cmd_exec(t_minishell *data, char **command, char **envp);

/* ================================= ERRORS ================================= */

/* ----------------------------------------------- minishell_error_handling.c */

void			handle_error(t_minishell *data, const char *str, int error);

/* ------------------------------------------------ minishell_error_logging.c */

void			ms_perror(t_minishell *data, const char *file);
void			log_syntax_error(t_token *token);

/* ------------------------------------------------- minishell_syntax_error.c */

bool			contains_syntax_error(t_token *list);
t_token			*syntax_error_at_token(t_token *list);

/* ================================== UTILS ================================= */

/* ------------------------------------------------- minishell_var_name_len.c */

size_t			var_name_len(const char *str);

/* -------------------------------------------------- minishell_print_debug.c */

void			print_debug_tokens(t_token *list);
void			print_debug(t_minishell *data);

/* ------------------------------------------ minishell_cleanup_and_exiting.c */

void			free_heap_memory(t_minishell *data);
void			close_fds(t_minishell *data);
void			clean(t_minishell *data);
void			clean_exit(t_minishell *data, int exit_code);
void			clean_error_exit(t_minishell *data, const char *msg, \
						int exit_code);

/* ------------------------------------------ minishell_cleanup_and_exiting.c */

bool			is_a_directory(t_minishell *data, const char *str);

/* ----------------------------------------- minishell_directory_validation.c */

bool			pretends_to_be_a_directory(t_minishell *data, const char *str);

/* ------------------------------------------- minishell_safe_fd_management.c */

void			try_to_close_fd(t_minishell *data, int *fd);
void			try_to_dup2(t_minishell *data, int fd1, int fd2);
void			redirect_stdout_and_close_fd(t_minishell *data, int *fd);
void			redirect_stdin_and_close_fd(t_minishell *data, int *fd);

/* ----------------------------------------- minishell_safe_pipe_management.c */

void			try_to_pipe(t_minishell *data, int *new_pipe);

/* --------------------------------------------- minishell_token_helpers_01.c */

t_token			*copy_tokens_within_pipe(t_minishell *data, \
								const t_token *start);
t_token			*copy_cmd_and_args_within_pipe(t_minishell *data, \
										const t_token *start);
t_token			*copy_redirections_within_pipe(t_minishell *data, \
										const t_token *start);
t_token			*copy_heredocs_within_pipe(t_minishell *data, \
									const t_token *start);

/* --------------------------------------------- minishell_token_helpers_02.c */

t_token			*skip_to_pipe_by_index(const t_minishell *data);

/* -------------------------------------------------------------------------- */

void			set_terminal(t_minishell *data);
void			execution(t_minishell *data);

#endif
