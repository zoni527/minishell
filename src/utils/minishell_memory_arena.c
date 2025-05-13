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

/* Utility wrapper functions for allocation, perform a clean exit on error. */

void	*ms_calloc(t_minishell *data, size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_ma_calloc(data->arena, nmemb, size);
	if (!ptr)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (ptr);
}

char	*ms_strdup(t_minishell *data, const char *s)
{
	char	*str;

	str = ft_ma_strdup(data->arena, s);
	if (!str)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (str);
}

char	*ms_strjoin(t_minishell *data, char const *s1, char const *s2)
{
	char	*joined_str;

	joined_str = ft_ma_strjoin(data->arena, s1, s2);
	if (!joined_str)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (joined_str);
}

char	*ms_substr(t_minishell *data, char const *s,
				unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_ma_substr(data->arena, s, start, len);
	if (!substr)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (substr);
}

char	**ms_split(t_minishell *data, char const *s, char c)
{
	char	**str_array;

	str_array = ft_ma_split(data->arena, s, c);
	if (!str_array)
		clean_error_exit(data, MSG_ERROR_ENOMEM, EXIT_ENOMEM);
	return (str_array);
}
