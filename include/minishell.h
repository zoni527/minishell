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
# include "../libft/libft.h"
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
/* -------------------------------------------------------------------- extra */
# include <stdbool.h>

/* =============================== MACROS =================================== */

/* -------------------------------------------------------- numeric constants */
// Default size is 10 MiB (1024^2)
# define MEM_ARENA_SIZE	1048576
/* -------------------------------------------------------------- error codes */
# define ERROR_PERMISSION	1
# define ERROR_ALLOC		2
# define ERROR_UNCLOSED		3
/* ----------------------------------------------------------- error messages */
# define MSG_ERROR_ALLOC	"ERROR: couldn't alloc"

# define METACHARACTERS	"|<> \t\n"

/* ================================ ENUMS ====================================*/

typedef enum e_token_type {
	WORD,				// No expansion or quote removal done yet
	COMMAND,			// First word or first word after operator
	ARGUMENT,			// Not first word
	BUILTIN,			// echo, cd, pwd, export, unset, env or exit
	PIPE,				// |
	REDIRECT_INPUT,		// <
	REDIRECT_OUTPUT,	// >
	HEREDOC,			// <<
	APPEND				// >>
}	t_token_type;

/* ============================== TYPEDEFS ===================================*/

typedef struct s_memarena	t_memarena;

typedef struct s_memarena {
	size_t		capacity;
	size_t		bytes_used;
	void		*heap_memory;
	t_memarena	*next;
}	t_memarena;

typedef struct s_minishell {
	t_memarena	*arena;
	t_list		*token_list;
	const char	*raw_input;
	const char	*env[];
}	t_minishell;

typedef struct s_token {
	t_token_type	type;
	const char		*value;
}	t_token;

/* ============================= TOKENIZATION =============================== */

/* --------------------------------------------- minishell_quote_validation.c */
bool	has_unclosed_quotes(const char *str);

/* ================================ UTILS =================================== */

/* ----------------------------------------------- minishell_utils_memarena.c */
void	*new_memarena(void);
void	*memarena_calloc(t_memarena *arena, size_t nmemb, size_t size);
void	free_memarena(t_memarena *arena);
/* -------------------------------------------------------------------------- */

#endif
