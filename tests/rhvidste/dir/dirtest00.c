/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtest00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:27:54 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/12 17:07:02 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
//# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//################################################LIBFT FUNTIONS###############################################################
// Strlen function
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

// Function to join strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	size_t			i;
	size_t			j;
	size_t			s1_len;
	size_t			s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

// Function to extract substring
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dest;
	size_t		i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		start = (unsigned int)ft_strlen(s);
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// Function to strn cmp and check wether EOF is entered or not
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

//###############################################PROGRM FUNTIONS########################################################################

// Function to print the current directory path
int	get_current_dir(void)
{
	char	*buffer = getcwd(NULL, 0); // Dynamically allocate memory
	
	if (buffer != NULL)
	{
		printf("Current working directory is: %s\n", buffer);
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

// FUnction to switch dir
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

// Function to check wether the built in "cd" is called
int	check_if_cd(const char *str)
{
	if (ft_strncmp("cd", str, 2) == 0)
		return (0);
	return (1);
} 


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	get_current_dir();

	char	*input;
	char	*path;
	char	*new_path;
	char	*home_path;

	while (1)
	{
		input = readline(">> ");
		if (!input)
			return (1);
		//Checking for exit case where "exit"
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			printf("exiting program...\n");
			free(input);
			break ;
		}
//		add_history(input);
//		printf("output of checkifcd is %d\n", check_if_cd(input));
		if (check_if_cd(input) == 0)
		{
			path = ft_substr(input, 3, (ft_strlen(input) - 2));

			printf("path = %s\n", path);
			if (path[0] == '~')
			{
				new_path = ft_substr(path, 1, (ft_strlen(path) - 1));
				printf("path == '~'\n");
				home_path = getenv("HOME");
				printf("newpath = %s%s\n", home_path, new_path);
			}
//			printf("cd detected\n");
			change_dir(path);
//			printf("substring out : %s\n",ft_substr(input, 2, (ft_strlen(input) - 2)));
		}
//		change_dir(input);
		get_current_dir();
//		printf("you shouted: %s into the void\n", input);
		add_history(input);
//		free(input);
//		printf("the void shouts back the following:\n");
//		print_history();
//		if (ft_strrchr(input, '<'))
//		{
//			printf("%s includes a '<' character\n", input);
//		}
		free(input);
	}

//	get_current_dir();
//	change_dir(argv[1]);
//	get_current_dir();
	return (0);
}
