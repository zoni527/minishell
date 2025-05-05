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

/* =============================== MACROS =================================== */

/* -------------------------------------------------------- numeric constants */

// Default size is 10 MiB (1024^2)
# define MEM_ARENA_SIZE	1048576
# define MAX_HEREDOCS	16

/* --------------------------------------------------------------- exit codes */

/* Execution exit values */
# define EXIT_LIMITHEREDOC	2
# define EXIT_HEREDOC_FILE	3
# define EXIT_BINPERM		126
# define EXIT_NOCMD			127
# define EXIT_EXECVE		128

/* Builtin exit values */
# define EXIT_BLTN_NAN		2
# define EXIT_BLTN_NOSUCH	5
# define EXIT_BLTN_TOOMANY	6

# define EXIT_ENOMEM		42

/* -------------------------------------------------------------------- colors*/

# define BHCYN	"\e[1;96m"
# define BGRN	"\e[1;32m"
# define CRESET	"\e[0m"

/* ---------------------------------------------------------- string literals */

# define STR_PROMPTSTART		"\e[1;96mminishell:\e[0m "
# define STR_PROMPTDELIM		" 🐢 "

/* ----------------------------------------------------------- error messages */

# define MSG_ERROR_CAPACITY		"ERROR: requested memory chunk is too large"
# define MSG_ERROR_OPEN			"ERROR: failed to open"
# define MSG_ERROR_CLOSE		"ERROR: failed to close"
# define MSG_ERROR_PIPE			"ERROR: failed to pipe"
# define MSG_ERROR_FORK			"ERROR: failed to fork"
# define MSG_ERROR_DUP			"ERROR: failed to dup"
# define MSG_ERROR_DUP2			"ERROR: failed to dup2"
# define MSG_ERROR_WRITE		"ERROR: failed to write"
# define MSG_ERROR_EXECVE		"ERROR: made it past execve"
# define MSG_ERROR_ENOMEM		"ERROR: system is out of memory"
# define MSG_ERROR_SYNTAX		"syntax error near unexpected token `"
# define MSG_ERROR_NOSUCH		"No such file or directory"
# define MSG_ERROR_TOOMANYARGS	"too many arguments"
# define MSG_ERROR_PERMISSION	"Permission denied"
# define MSG_ERROR_ISADIR		"Is a directory"
# define MSG_ERROR_NOTADIR		"Not a directory"
# define MSG_ERROR_LIMITHEREDOC	"Maximum heredoc count exceeded"
# define MSG_ERROR_HEREDOC		"Heredoc execution failed"
# define MSG_ERROR_HEREDOC_FILE	"Failed to open heredoc temp file"
# define MSG_ERROR_NODELIM		"EOF received instead of delimiter"
# define MSG_ERROR_UNCLOSED		"Input has unclosed quotes"
# define MSG_ERROR_BLTN_NOSUCH	"No matching builtin could be found"
# define MSG_ERROR_NOCMD		"command not found"

# define METACHARACTERS			"|<> \t\n"

# ifndef READ
#  define READ	0
# endif

# ifndef WRITE
#  define WRITE	1
# endif

/* ================================ ENUMS =================================== */

// libft.h: ERROR_ALLOC		2
// libft.h: ERROR_CAPACITY	3

typedef enum e_error
{
	ERROR_PIPE = 4,
	ERROR_FORK,
	ERROR_DUP,
	ERROR_DUP2,
	ERROR_OPEN,
	ERROR_CLOSE,
	ERROR_EXECVE,
	ERROR_ACCESS,
	ERROR_GETCWD,
	ERROR_CHDIR,
	ERROR_NOPATH,
	ERROR_INPUT,
	ERROR_UNLINK,
	ERROR_UNCLOSED,
	ERROR_TCGETATTR,
	ERROR_TCSETATTR,
	ERROR_ENOMEM,
	ERROR_HEREDOC,
	ERROR_WRITE,
	ERROR_NODELIM,
	ERROR_NOSUCH,
	ERROR_PERMISSION,
	ERROR_ISADIR,
	ERROR_NOTADIR,
	ERROR_NOCMD,
	ERROR_BINPERM,
	ERROR_BINISADIR,
	ERROR_BINNOTADIR,
	ERROR_LIMITHEREDOC,
}	t_error;

typedef enum e_token_type
{
	WORD,
	COMMAND,
	ARGUMENT,
	BUILTIN,
	FILE_NAME,
	DELIMITER,
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
	size_t				hd_count;
	size_t				var_count;
	size_t				pipe_index;
	pid_t				last_pid;
	int					last_rval;
	int					pipe_fds[2];
	struct sigaction	act_int;
	struct sigaction	act_int_old;
	struct sigaction	act_quit;
	struct sigaction	act_quit_old;
	const char			*raw_input;
	const char			**initial_env;
	const char			**hd_delimiters;
	const char			**hd_file_names;
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
	char			*value;
	t_token			*next;
	t_token			*prev;
}	t_token;

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
bool			is_word(const t_token *token);
bool			is_delimiter(const t_token *token);

/* ----------------------------------------- minishell_assign_token_indices.c */

void			assign_token_indices(t_minishell *data);

/* ------------------------------------------------ minishell_token_getters.c */

t_bltn_type		get_builtin_type(const t_token *token);
const char		*get_token_type_str(const t_token *token);

/* ----------------------------------------------- minishell_token_analysis.c */

size_t			count_tokens(const t_token *list);
size_t			count_pipes(const t_token *list);
size_t			count_heredocs(const t_token *list);
size_t			count_vars(const t_var *list);

/* ------------------------------------------- minishell_tokenization_utils.c */

void			toggle_quote_flag(char *quote_flag, char c);
t_token			*new_token_node(t_minishell *data, const char *str);
void			append_token(t_token **list, t_token *token);
void			insert_token_left(t_token *current, t_token *new);

/* =============================== ENVIRONMENT ============================== */

/* -------------------------------------------- minishell_environment_shell.c */

void			set_shell_lvl(t_minishell *data);

/* ------------------------------------------- minishell_environment_export.c */

int				ms_setenv_export(t_minishell *data, char *key,
					char *value, char *raw);

/* -------------------------------------- minishell_environment_print_alpha.c */

void			print_env_alphabetically(t_minishell *data);

/* ----------------------------------------------- minishell_environment_01.c */

char			*ms_getenv(t_minishell *data, char *key);
int				ms_setenv(t_minishell *data, char *key, char *value);
int				remove_env(char *key, t_var *envp);

/* ----------------------------------------------- minishell_environment_02.c */

void			env_list_from_envp(t_minishell *data, const char **envp);
char			**create_envp_arr_from_custom_env(t_minishell *data,
					t_var *envp_list);

/* --------------------------------------------- minishell_environment_list.c */

int				get_env_list_size(t_var *begin);
void			print_custom_env(t_var *list);
t_var			*create_new_env_var(t_minishell *data,
					char *raw, char *key, char *value);

/* ================================ BUILTINS ================================ */

/* ---------------------------------------------- minishell_builtin_handler.c */

t_token			*fetch_builtin(t_minishell *data);
int				builtins(t_minishell *data);

/* -------------------------------------------------- minishell_builtin_dir.c */

int				get_current_dir(t_minishell *data);
int				change_dir(t_minishell *data, char *str);
char			*safe_getcwd(t_minishell *data);

/* ------------------------------------------------- minishell_builtin_echo.c */

void			builtin_echo(t_minishell *data);

/* ------------------------------------------------ minishell_builtin_cd_01.c */

void			builtin_cd(t_minishell *data);

/* ------------------------------------------------ minishell_builtin_cd_02.c */

int				handle_cd(t_minishell *data, t_token *cd_tokens, char *path);

/* -------------------------------------------------- minishell_builtin_pwd.c */

void			builtin_pwd(t_minishell *data);

/* -------------------------------------------- minishell_builtin_export_01.c */

void			builtin_export(t_minishell *data);

/* -------------------------------------------- minishell_builtin_export_02.c */

void			set_key_and_value(t_minishell *data, t_token *token);

/* -------------------------------------------- minishell_builtin_export_03.c */

char			*create_raw(t_minishell *data, char *key, char *value);

/* ------------------------------------------------ minishell_builtin_unset.c */

void			builtin_unset(t_minishell *data);

/* -------------------------------------------------- minishell_builtin_env.c */

void			builtin_env(t_minishell *data);

/* ------------------------------------------------- minishell_builtin_exit.c */

int				builtin_exit(t_minishell *data);

/* ================================= PIPING ================================= */

/* ---------------------------------------------------- minishell_piping_01.c */

void			piping(t_minishell *data);

/* ---------------------------------------------------- minishell_piping_02.c */

void			child_process(t_minishell *data);

/* ================================= SIGNALS ================================ */

/* ------------------------------------------------------ minishell_signals.c */

void			set_and_activate_primary_signal_handler(t_minishell *data);
void			activate_primary_signal_handler(t_minishell *data);
void			activate_secondary_signal_handler(t_minishell *data);

/* ============================== REDIRECTIONS ============================== */

/* -------------------------------------------- minishell_pipe_redirections.c */

int				handle_redirections(t_minishell *data);

/* ----------------------------------------------- minishell_redirect_input.c */

int				redirect_input(t_minishell *data, const t_token *input);

/* ---------------------------------------------- minishell_redirect_output.c */

int				redirect_output(t_minishell *data, const t_token *output);
int				validate_outfile(t_minishell *data, const char *file_name);

/* --------------------------------------------- minishell_redirect_heredoc.c */

int				redirect_heredoc(t_minishell *data, const t_token *heredoc);

/* ---------------------------------------------- minishell_redirect_append.c */

int				redirect_append(t_minishell *data, const t_token *append);

/* --------------------------------------------------- minishell_heredoc_01.c */

int				heredoc(t_minishell *data);

/* --------------------------------------------------- minishell_heredoc_02.c */

char			*read_heredoc_input(t_minishell *data, const char *delimiter);
t_token			*skip_to_heredoc(const t_token *list);

/* =============================== EXECUTION ================================ */

/* ---------------------------------------------------- minishell_execution.c */

char			**create_args_arr(t_minishell *data, t_token *command);
void			cmd_exec(t_minishell *data, char **command, char **envp);

/* --------------------------------------------- minishell_input_validation.c */

int				validate_raw_input(const t_minishell *data);
int				validate_tokens(t_minishell *data);

/* ----------------------------------------------- minishell_single_builtin.c */

void			run_single_builtin(t_minishell *data);

/* ================================= ERRORS ================================= */

/* ----------------------------------------------- minishell_error_handling.c */

void			handle_error(t_minishell *data, const char *str, t_error error);

/* ------------------------------------------------ minishell_error_logging.c */

void			ms_perror(t_minishell *data, const char *file);
void			log_syntax_error(t_token *token);

/* ------------------------------------------------- minishell_syntax_error.c */

bool			contains_syntax_error(t_token *list);
t_token			*syntax_error_at_token(t_token *list);

/* ------------------------------------------ minishell_exit_value_handling.c */

void			match_exit_value_to_error(t_minishell *data, t_error error);

/* ================================== UTILS ================================= */

/* -------------------------------------------- minishell_environment_utils.c */

int				get_envp_len(t_var *envp);

/* ------------------------------------------------- minishell_var_name_len.c */

size_t			var_name_len(const char *str);

/* -------------------------------------------------- minishell_print_debug.c */

void			print_debug_tokens(const t_token *list);
void			print_debug(const t_minishell *data);

/* ------------------------------------------ minishell_cleanup_and_exiting.c */

void			free_heap_memory(t_minishell *data);
void			close_fds(t_minishell *data);
void			clean(t_minishell *data);
void			clean_exit(t_minishell *data, int exit_code);
void			clean_error_exit(t_minishell *data, const char *msg,
					int exit_code);

/* ------------------------------------------ minishell_cleanup_and_exiting.c */

bool			is_a_directory(t_minishell *data, const char *str);

/* ----------------------------------------- minishell_directory_validation.c */

bool			pretends_to_be_a_directory(t_minishell *data, const char *str);

/* ------------------------------------------- minishell_safe_fd_management.c */

void			safe_close(t_minishell *data, int *fd);
void			safe_dup2(t_minishell *data, int fd1, int fd2);
int				safe_dup(t_minishell *data, int fd);
void			redirect_stdout_and_close_fd(t_minishell *data, int *fd);
void			redirect_stdin_and_close_fd(t_minishell *data, int *fd);

/* ----------------------------------------- minishell_safe_pipe_management.c */

void			safe_pipe(t_minishell *data, int *new_pipe);

/* --------------------------------------------- minishell_token_helpers_01.c */

t_token			*copy_tokens_within_pipe(const t_minishell *data);
t_token			*copy_cmd_and_args_within_pipe(const t_minishell *data);
t_token			*copy_redirections_within_pipe(const t_minishell *data);
t_token			*copy_token(const t_minishell *data, const t_token *token);

/* --------------------------------------------- minishell_token_helpers_02.c */

t_token			*skip_to(const t_token *list,
					bool (*f)(const t_token *token));
t_token			*skip_to_next(const t_token *list,
					bool (*f)(const t_token *token));
t_token			*skip_to_current_pipe(const t_minishell *data);
bool			tokens_contain(const t_token *list,
					bool (*f)(const t_token *token));
bool			pipe_has(const t_minishell *data,
					bool (*f)(const t_token *token));

/* --------------------------------------------- minishell_token_helpers_03.c */

bool			pipe_has_redirections(const t_minishell *data);
bool			pipe_has_heredoc(const t_minishell *data);
bool			pipe_has_input_redirection(const t_minishell *data);
bool			pipe_has_output_redirection(const t_minishell *data);
bool			pipe_has_append(const t_minishell *data);

/* ------------------------------------------------ minishell_data_reset_01.c */

int				reset_data(t_minishell *data);

/* ------------------------------------------------ minishell_data_reset_02.c */

t_var			*copy_env_to_memarena(t_memarena *arena, const t_var *env_list);
void			append_var(t_var **env_list, t_var *var);

/* -------------------------------------------------------------------------- */
#endif
