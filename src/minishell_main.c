/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:41:42 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 12:26:27 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	static t_minishell	data;

	data.arena = new_memarena();
	if (!data.arena)
		return (ERROR_ALLOC);
	free_memarena(data.arena);
	return (0);
}
