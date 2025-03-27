/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:09:56 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/27 10:33:24 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* =============================== HEADERS ================================== */

/* -------------------------------------------------------------------- libft */

# include "libft.h"

/* ---------------------------------------------------------------- minishell */

# include <readline/readline.h>
# include <stdio.h>
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

# define ERROR_PERMISSION	1
# define ERROR_ALLOC		2
# define ERROR_UNCLOSED		3
# define ERROR_CAPACITY		4

/* ----------------------------------------------------------- error messages */

# define MSG_ERROR_ALLOC	"ERROR: couldn't alloc"
# define MSG_ERROR_CAPACITY	"ERROR: requested memory chunk is too large"

# define METACHARACTERS			"|<> \t\n"

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

/* ============================== TYPEDEFS ================================== */

typedef struct s_token		t_token;
typedef struct s_var		t_var;

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
	t_memarena	*arena;
	t_token		*token_list;
	t_var		*custom_env;
	size_t		token_count;
	const char	*raw_input;
	const char	*initial_env[];
}	t_minishell;

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

/* ================================ UTILS =================================== */

/* ------------------------------------------------- minishell_var_name_len.c */

size_t		var_name_len(const char *str);

/* -------------------------------------------------- minishell_print_debug.c */

void		print_debug_tokens(t_token *list);
void		print_debug(t_minishell *data);

/* -------------------------------------------------------------------------- */
#endif
