/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:04:31 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:08:13 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to free an array
 *
 * @param arr	arr to free
 */
int	free_array(char **arr)
{
	int	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	return(0);
}

/**
 * Function to remove single and double quotes from a string
 *
 * @param str	input string
 */
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		count;
	int		in_double_quotes;
	char	*dest;
	
	in_double_quotes = 0;
	count = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			in_double_quotes = !in_double_quotes;
			count++;
		}
		else if(str[i] == '\'' && !in_double_quotes)
			count++;	
	}
	dest = malloc(sizeof(char) * (i - count) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	in_double_quotes = 0;
	while(str[i])
	{
		if (str[i] == '"')
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else if (str[i] == '\'' && !in_double_quotes)
			i++;
		else
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (dest);
}
