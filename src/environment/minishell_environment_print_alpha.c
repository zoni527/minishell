/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_print_alpha.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:04:06 by rhvidste          #+#    #+#             */
/*   Updated: 2025/04/17 15:10:31 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to get the length of the
 * envp list
 *
 * @param envp	pointer to the fist envp element
 */

int	get_envp_len(t_var *envp)
{
	if (envp == 0)
		return (0);
	else
		return (1 + get_envp_len(envp->next));
}

/**
 * Function to get the largest element
 * from the envp list
 *
 * @param envp	pointer to the fist envp element
 */
static t_var	*get_largest(t_var *envp)
{
	t_var	*token;
	t_var	*largest;

	token = envp;
	largest = token;
	while (token)
	{
		if (ft_strcmp(largest->key, token->key) < 0)
		{
			largest = token;
		}
		token = token->next;
	}
	return (largest);
}

/**
 * Function to get the smallest element
 * from the envp list
 *
 * @param envp	pointer to the fist envp element
 */
static t_var	*get_smallest(t_var *envp)
{
	t_var	*token;
	t_var	*smallest;

	token = envp;
	smallest = token;
	while (token)
	{
		if (ft_strcmp(smallest->key, token->key) > 0)
		{
			smallest = token;
		}
		token = token->next;
	}
	return (smallest);
}

/**
 * Function to print next env element 
 * in alphabetical order
 *
 * @param envp	pointer to the fist envp element
 * @param smallest	pointer to the smallest element in the env
 * @param largest	pointer to the largest element in the env
 * @param len	len of the envp list
 */
static void	print_next(t_var *envp, t_var *smallest, t_var *largest, int len)
{
	t_var	*next_smallest;
	t_var	*last_elem;
	t_var	*token;
	int		i;

	token = envp;
	last_elem = smallest;
	next_smallest = largest;
	ft_putendl_fd(smallest->raw, 1);
	i = -1;
	while (++i < (len - 1))
	{
		while (token)
		{
			if (strcmp(token->key, last_elem->key) > 0 && \
				strcmp(token->key, next_smallest->key) < 0)
				next_smallest = token;
			token = token->next;
		}
		ft_putendl_fd(next_smallest->raw, 1);
		token = envp;
		last_elem = next_smallest;
		next_smallest = largest;
	}
}

/**
 * Function to print env in alphabetical order
 *
 * @param envp	pinter to the fist envp element
 */
void	print_env_alphabetically(t_var *envp)
{
	t_var	*smallest;
	t_var	*largest;
	int		len;

	len = get_envp_len(envp);
	largest = get_largest(envp);
	smallest = get_smallest(envp);
	print_next(envp, smallest, largest, len);
}
