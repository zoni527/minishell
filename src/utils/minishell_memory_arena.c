/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_memory_arena.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:09:27 by jvarila           #+#    #+#             */
/*   Updated: 2025/05/13 09:23:37 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * Wrapper function for ft_ma_calloc, which allocates memory from data->arena.
 * Performs a clean exit if there is no more memory available.
 *
 * @param data		Pointer to main data struct
 * @param nmbemb	Number of elements to allocate
 * @param size		Size of elements to allocate
 *
 * @return	Pointer to requested memory
 */
void	*ms_calloc(t_minishell *data, size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_ma_calloc(data->arena, nmemb, size);
	if (!ptr)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (ptr);
}

/**
 * Wrapper function for ft_ma_strdup. Duplicates a string into data->arena.
 * Performs a clean exit if there is no more memory available.
 *
 * @param data		Pointer to main data struct
 * @param s			String to duplicate
 *
 * @return	Pointer to duplicated string in data->arena
 */
char	*ms_strdup(t_minishell *data, const char *s)
{
	char	*str;

	str = ft_ma_strdup(data->arena, s);
	if (!str)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (str);
}

/**
 * Wrapper function for ft_ma_strjoin. Joins two strings and returns the
 * new string that is saved in data->arena.
 * Performs a clean exit if there is no more memory available.
 *
 * @param data	Pointer to main data struct
 * @param s1	First string to be joined
 * @param s2	Second string to be joined
 *
 * @return	Pointer to joined string in data->arena
 */
char	*ms_strjoin(t_minishell *data, char const *s1, char const *s2)
{
	char	*joined_str;

	joined_str = ft_ma_strjoin(data->arena, s1, s2);
	if (!joined_str)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (joined_str);
}

/**
 * Wrapper function for ft_ma_substr. Creates a substring inside data->arena.
 * Performs a clean exit if there is no more memory available.
 *
 * @param data	Pointer to main data struct
 * @param s		String to create substring from
 * @param start	Starting index of substring
 * @param len	Lenght of substring
 *
 * @return	Pointer to substring in data->arena
 */
char	*ms_substr(t_minishell *data, char const *s,
				unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_ma_substr(data->arena, s, start, len);
	if (!substr)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (substr);
}

/**
 * Wrapper function for ft_ma_split. Creates a null terminated array of strings
 * inside data->arena. Performs a clean exit if there is no more memory
 * available.
 *
 * @param data	Pointer to main data struct
 * @param s		String to be split
 * @param c		Character to split the string by
 *
 * @return	Pointer to first element in array of strings in data->arena
 */
char	**ms_split(t_minishell *data, char const *s, char c)
{
	char	**str_array;

	str_array = ft_ma_split(data->arena, s, c);
	if (!str_array)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (str_array);
}
