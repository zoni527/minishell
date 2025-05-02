/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_03.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:11:19 by rhvidste          #+#    #+#             */
/*   Updated: 2025/05/02 16:12:01 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to create a raw value for a enviroment 
 * variable 
 * called from within BUILTIN EXPORT
 *
 * @param data	pointer to the main data struct
 * @param key	key value 
 * @param value	value value 
 */
char	*create_raw(t_minishell *data, char *key, char *value)
{
	char	*raw;

	raw = ft_ma_strjoin(data->arena, key, "=");
	raw = ft_ma_strjoin(data->arena, raw, value);
	return (raw);
}
