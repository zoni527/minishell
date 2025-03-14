/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:58:15 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/14 15:00:43 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


int	main(int argc, char **argv)
{
	int	i = 1;
	while (i < argc)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}
