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

#include "../../include/minishell.h"

/**
 * ERRORS
 *		Return NULL if there is no more heap memory available
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
	return (arena);
}

/**
 * ERRORS
 *		Return NULL if there is no more heap memory available
 */
void	*memarena_calloc(t_memarena *arena, size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes_required;
	size_t	bytes_available;

	bytes_required = nmemb * size;
	if (bytes_required > arena->capacity)
		return (NULL);
	bytes_available = arena->capacity - arena->bytes_used;
	while (bytes_available < bytes_required)
	{
		if (!arena->next)
			arena->next = new_memarena();
		if (!arena->next)
			return (NULL);
		arena = arena->next;
		bytes_available = arena->capacity - arena->bytes_used;
	}
	ptr = arena->heap_memory + arena->bytes_used;
	arena->bytes_used += bytes_required;
	return (ptr);
}

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
