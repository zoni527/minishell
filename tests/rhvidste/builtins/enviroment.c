/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:12:19 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/21 12:16:13 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/minishell.h"

/**
 * Function to parse the envp into
 * a linked list for later use
 *
 * @param data	Main data struct
 * @param envp	system envp input
 */
void	parse_env(t_minishell *data, char **envp)
{
	t_var	*head = NULL;
	t_var	*current = NULL;
	char	*raw;
	char	*key;
	char	*value;
	int		i;
	int		j;
	
	i = -1;
	while (envp[++i])
	{
		raw = ft_strdup(envp[i]);
		j = 0;
		while (raw[j] != '=')
		{
			j++;
		}
		key = ft_substr(raw, 0, j);
		value = ft_substr(raw, (j + 1), ft_strlen(raw) - (j + 1));
		
		if (head == NULL)
		{
			head = append_node(NULL, raw, key, value);
			current = head;
			data->custom_env = head;
		}
		else
		{
			current->next = append_node(current, raw, key, value);
			current = current->next;
		}
	}
//	data.custom_env = &(t_var){.raw = "ARG=test test", .key = "ARG", .value = "|test|"};
//	data.custom_env->next = &(t_var){.raw = "", .key = "DERP", .value = "|derp|"};
}

/**
 * Function to convert envp_list to an NULL terminated
 * array of strings
 *
 * @param envp	pointer to first envp element
 */
char	**convert_envp_to_arr(t_var *envp_list)
{
	t_var	*head;
	t_var	*current;
	char	**envp_arr;
	int		list_len;
	int		i;

	i = -1;
	list_len = 0;
	head = NULL;
	current = NULL;

	//lets get the lengnth of the list
	list_len = get_list_size(envp_list);
	//using the list len to malloc the str arr
	envp_arr = malloc(sizeof(char *) * list_len + 1);

	head = envp_list;
	current = head;
	//now create the array using the raw value from the list
	while (++i < list_len)
	{
		envp_arr[i] = current->raw;
		current = current->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

/**
 * Function to get specific envp variable from the list
 * and return it in a variable
 *
 * @param name	name of target envp variable
 * @param envp	pointer to first envp element
 */
char	*ft_getenv(const char *name, t_var *envp)
{
	t_var	*current;
	char	*sub_name;
	char	*envar;

//	sub_name = NULL;
	if (!name || !envp)
		return (NULL);
	current = NULL;
	if (ft_strncmp(name, "getenv", 6) == 0)
		sub_name = ft_substr(name, 7, ft_strlen(name) - 6);
	else
		sub_name = ft_strdup(name);
	if (!sub_name)
		return (NULL);
	current = envp;
	while (current)
	{
		if (ft_strncmp(sub_name, current->key, ft_strlen(sub_name)) == 0)
		{
			envar = ft_strdup(current->value);
			free(sub_name);
			ft_putendl_fd(envar, 1);
			return (envar);
		}
		else
			current = current->next;
	}
	free(sub_name);
	return (NULL);
}

/**
 * Function to set or create a envp variable
 *
 * @param name	key input
 * @param value	value input
 * @param envp	enviroment pointer
 */
int	ft_setenv(char *key, char *value, t_var *envp)
{
	char	*raw;
//	t_var	*new_node;
	t_var	*current;
	t_var	*last;

//	new_node = NULL;
	current = NULL;
	last = NULL;

	raw = ft_strjoin(key, "=");
	raw = ft_strjoin(raw, value);
	//first checking to see if the var exists, if it does then chagnes only the value
	current = envp;
	while (current)
	{
		if (strncmp(key, current->key, ft_strlen(key)) == 0)
		{
			current->raw = raw;
			current->value = value;
			return (0);
		}
		last = current;
		current = current->next;
	}
	//Else if variable does not exist, then create it
	if (last)
		last->next = append_node(last, raw, key, value);
	return (0);
}

/**
 * Function to remove an envp variable
 *
 * @param name	key input
 * @param envp	enviroment pointer
 */
int	remove_env(char *key, t_var *envp)
{
	t_var	*current;

	current = NULL;

	current = envp;
	while (current)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0)
		{
			if (current->next == NULL)
			{
				current->prev->next = NULL;
				return (0);
			}
			current->next->prev = current->prev;
			current->prev->next = current->next;
			return (0);
		}
		current = current->next;
	}
	return (0);	
}
