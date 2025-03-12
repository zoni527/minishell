/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtest00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:27:54 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/12 11:50:56 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

int	get_current_dir(void)
{
	char	*buffer = getcwd(NULL, 0); // Dynamically allocate memory
	
	if (buffer != NULL)
	{
		printf("Current working director is: %s\n", buffer);
		free (buffer);
	}
	else
	{
		perror("getcwd error");
		return (1);
	}
	return (0);
//	char buffer[1024];
//
//	if (getcwd(buffer, sizeof(buffer)) !=NULL)
//	{
//		printf("Current working directory: %s\n", buffer);
//	}
//	else
//	{
//		perror("getcwd error");
//	}
//	return (0);
}

int	change_dir(char *str)
{
	if (chdir(str) == 0)
	{
		printf("Directory changed successfully\n");
	}
	else
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
//	int	result;
//	result = chdir(str);
//	if (result == 0)
//	{
//		printf("Directory changed successfully\n");
//	}
//	else 
//	{
//		perror("Error changing directory");
//		return (1);
//	}
//	return (0);
}


int	main(int argc, char **argv)
{
	(void)argc;
	get_current_dir();
	change_dir(argv[1]);
	get_current_dir();
	return (0);
}
