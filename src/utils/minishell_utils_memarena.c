/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_memarena.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:27:49 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 14:46:08 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 *     To be used like calloc, returns a pointer that is pointing to memory
 *     that is inside the memory arena's pool of heap memory.
 *
 * NOTE
 *     If no memory is available this functions calls free_arena_exit
 *     wich terminates the program.
 */
void	*memarena_calloc(t_memarena *arena, size_t nmemb, size_t size)
{
	t_memarena	*initial_arena;
	void		*ptr;
	size_t		bytes_required;
	size_t		bytes_available;

	bytes_required = nmemb * size;
	if (bytes_required > arena->capacity)
		free_memarena_exit(arena, MSG_ERROR_CAPACITY);
	bytes_available = arena->capacity - arena->bytes_used;
	initial_arena = arena;
	while (bytes_available < bytes_required)
	{
		if (!arena->next)
			arena->next = new_memarena();
		if (!arena->next)
			free_memarena_exit(initial_arena, MSG_ERROR_ALLOC);
		arena = arena->next;
		bytes_available = arena->capacity - arena->bytes_used;
	}
	ptr = arena->heap_memory + arena->bytes_used;
	arena->bytes_used += bytes_required;
	return (ptr);
}

/**
 * DESCRIPTION
 *     Creates new memarena struct with MEM_ARENA_SIZE bytes of heap memory.
 *
 * ERRORS
 *     Return NULL if ft_calloc can't return heap memory.
 */
void	*new_memarena(void)
{
	t_memarena	*arena;

	arena = ft_calloc(1, sizeof(t_memarena));
	if (!arena)
		return (NULL);
	arena->heap_memory = ft_calloc(1, MEM_ARENA_SIZE);
	if (!arena->heap_memory)
	{
		free(arena);
		return (NULL);
	}
	arena->capacity = MEM_ARENA_SIZE;
	arena->bytes_used = 0;
	return (arena);
}

void	free_memarena_exit(t_memarena *arena, const char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	free_memarena(arena);
	exit(ERROR_ALLOC);
}

/**
 * DESCRIPTION
 *     Goes through the linked list of arenas, freeing everything.
 *
 * NOTE
 *     Important to call with the root node when trying to feel all used memory.
 */
void	free_memarena(t_memarena *arena)
{
	t_memarena	*current;
	t_memarena	*next;

	current = arena;
	while (current)
	{
		next = current->next;
		free(current->heap_memory);
		free(current);
		current = next;
	}
}

void	reset_memarena(t_memarena *arena)
{
	if (arena->next)
		free_memarena(arena->next);
	ft_memset(arena->heap_memory, 0, MEM_ARENA_SIZE);
	arena->bytes_used = 0;
}
