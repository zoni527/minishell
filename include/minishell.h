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

/*--------------------------------------------------------------------- libft */
# include "../libft/libft.h"
/*----------------------------------------------------------------- minishell */
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <term.h>
/*--------------------------------------------------------------------- extra */
# include <stdbool.h>
/*----------------------------------------------------------------------------*/
// char	*operators[] = {"<", ">", "|", "<<", ">>", NULL};

// Default size is 10 MiB
# define MEM_ARENA_SIZE	1048576

typedef struct s_memarena t_memarena;

typedef struct s_memarena {
	size_t		capacity;
	size_t		offset;
	void		*heap_memory;
	t_memarena	*next;
}	t_memarena;

typedef struct s_minishell {
	t_memarena	arena;
	const char	*raw_input;
	const char	*env[];
}	t_minishell;


#endif
