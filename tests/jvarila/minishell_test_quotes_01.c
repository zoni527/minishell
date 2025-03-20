/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_quotes_01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:03:29 by jvarila           #+#    #+#             */
/*   Updated: 2025/03/11 17:09:38 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (ft_write_error_return_int("ERROR: give one argument", 1));
	ft_printf("Argument received: %s\n", argv[1]);
	if (has_unclosed_quotes(argv[1]))
		ft_printf("Argument %s has unclosed quotes\n", argv[1]);
	return (0);
}
