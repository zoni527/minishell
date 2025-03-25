/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:09:56 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 11:48:29 by jvarila          ###   ########.fr       */
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
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	APPEND
}	t_token_type;

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
	size_t			id;
	t_token			*next;
	t_token			*prev;
	const char		*value;
}	t_token;

/* ============================= TOKENIZATION =============================== */

/* --------------------------------------------- minishell_quote_validation.c */

bool	has_unclosed_quotes(const char *str);

/* ---------------------------------------------- minishell_tokenization_01.c */

void	lex_raw_input(t_minishell *data);
void	tokenize(t_minishell *data, const char *src, size_t len);
void	print_tokens(t_minishell *data);

/* ---------------------------------------------- minishell_tokenization_02.c */

t_token	*new_token_node(t_memarena *arena, const char *str);
void	append_token(t_token **list, t_token *token);
void	insert_token_right(t_token *current, t_token *new);
void	insert_token_left(t_token *current, t_token *new);

/* ------------------------------------------------ minishell_quote_removal.c */

void	quote_removal(t_minishell *data);

/* ============================== EXPANSION ================================= */

/* ------------------------------------------------- minishell_expansion_01.c */

void	variable_expansion(t_minishell *data);
void	expand_variables(t_minishell *data, t_token *token);
size_t	expand_variable(t_minishell *data, t_token *token, \
					t_var *var, size_t var_index);
bool	contains_unexpanded_variable(t_token *token);
t_var	*find_var(t_minishell *data, const char *str);

/* ------------------------------------------------- minishell_expansion_02.c */

void	toggle_quote_flag(char *quote_flag, char c);

/* ================================ UTILS =================================== */

/* ------------------------------------------------- minishell_var_name_len.c */

size_t	var_name_len(const char *str);

#endif
