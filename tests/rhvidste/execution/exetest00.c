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

# include "include/dir.h"

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
//	if (chdir(str) == 0)
//	{
//		printf("Directory changed successfully\n");
//	}
//	else
//	{
//		perror("chdir() error");
//		return (1);
//	}
	if (chdir(str) == -1)
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

// Function to check wether its one of the builtins.
int	check_if_builtin(const char *str)
{
	if (ft_strncmp("echo", str, 4) == 0)
		return (0);
	if (ft_strncmp("cd", str, 2) == 0)
		return (0);
	if (ft_strncmp("pwd", str, 3) == 0)
		return (0);
	if (ft_strncmp("export", str, 6) == 0)
		return (0);
	if (ft_strncmp("unset", str, 5) == 0)
		return (0);
	if (ft_strncmp("env", str, 3) == 0)
		return (0);
	if (ft_strncmp("exit", str, 4) == 0)
		return (0);
	return (1);
}

// Function to check wether the build in "echo" is called
int	check_if_echo(const char *str)
{
	if (ft_strncmp("cd", str, 2) == 0)
		return (0);
	return (1);
}

// Function to check wether the built in "cd" is called
int	check_if_cd(const char *str)
{
	if (ft_strncmp("cd", str, 2) == 0)
		return (0);
	return (1);
}

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

//###############################################PROGRAM EXECUTION(from pipex)############################################
char	*set_paths(char *command, char **mypaths)
{
	bool	it_works;
	char	*fullpath;
	char	*onepath;
	int		i;

	i = 0;
	it_works = false;
	while (mypaths[i])
	{
		onepath = ft_strjoin(mypaths[i], "/");
		fullpath = ft_strjoin(onepath, command);
//		printf("onepath = %s\n", onepath);
//		printf("fullpath = %s\n", fullpath);
		free(onepath);
		if (access(fullpath, F_OK) == 0)
		{
			it_works = true;
			break ;
		}
		else
			free(fullpath);
		i++;
	}	
	free_array(mypaths);
	if (it_works)
		return (fullpath);
	return (NULL);
}

char	*path_parsing(char *command, char **envp)
{
	char	**mypaths;
	char	*fullpath;
	int		i;

	if (command[0] == '.' && command[1] == '/')
	{
//		printf("COMMAND IS BINARY!!\n");
		fullpath = ft_strdup(command);
		return (fullpath);
	}
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	mypaths = ft_split(envp[i] + 5, ':');
	i = 0;
	fullpath = set_paths(command, mypaths);
	return (fullpath);
}

void	cmd_exec(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int		i;

	i = -1;
	command = ft_split(argv, ' ');
	path = path_parsing(command[0], envp);

//	while (command[++i])
//	{
//		printf("command is: %s\n", command[i]);
//	}
//	printf("path is: %s\n", path);

	if (!path)
	{
		free_array(command);
		exit(1);
	}
	if (execve(path, command, envp) == -1)
	{
		printf("execve failed");
		free_array(command);
		free(path);
	}
	perror("execve failed");
	free_array(command);
	free(path);
}

// Function to run executibal from path.
int	run_prog(char *input, char **envp)
{
	(void)input;
	(void)envp;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}

	if (pid == 0)
	{
//		char	*argv[] = {
//				"nvim",
//				"test.txt",
//				NULL
//		};
//
//		execve("/home/rhvidste/.local/bin/nvim-linux-x86_64/bin/nvim", argv, envp);
//
		cmd_exec(input, envp);
		perror("execve failed");
		exit(1);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
//		printf("program closed. Resuming parent process...\n");
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
//	(void)envp;
	
//	get_current_dir();

	char	*input;
	char	*path;
	char	*new_path;
	char	*home_path;
	char	*new_home_path;
	char	*shell_dir;

	while (1)
	{	
		char	*buffer = getcwd(NULL, 0); // Dynamically allocate memory
		shell_dir = ft_strjoin("mini_shell: ", buffer);
		shell_dir = ft_strjoin(shell_dir, "$ ");
		input = readline(shell_dir);
//		input = readline(">> ");
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
		if (check_if_builtin(input) == 0)
		{
			if (check_if_echo(input) == 0)
			{
				printf("ECHO called\n");
			}
			if (check_if_cd(input) == 0)
			{
				path = ft_substr(input, 3, (ft_strlen(input) - 2));
//				printf("path = %s\n", path);
				if (path[0] == '~')
				{
					new_path = ft_substr(path, 1, (ft_strlen(path) - 1));
//					printf("path == '~'\n");
					home_path = getenv("HOME");
//					printf("newpath = %s%s\n", home_path, new_path);
					new_home_path = ft_strjoin(home_path, new_path);
					change_dir(new_home_path);
					free(new_home_path);
					free(new_path);
				}
				//Here we check is CD is just added on its own.
				else if (path[0] == '\0')
				{
//					printf("CD COMMAND ENTERED\n");
					home_path = getenv("HOME");
					change_dir(home_path);
				}
				else
				{
//					printf("cd detected\n");
					change_dir(path);
//					input = readline("<< ");
//					printf("substring out : %s\n",ft_substr(input, 2, (ft_strlen(input) - 2)));
				}
				free(path);
			}
			else
			{
				run_prog(input, envp);
			}
		}
//		change_dir(input);
//		add_history(input);
//		get_current_dir();
//		if (check_if_cd(input) != 0)
//		{
//			printf("argument is not cd\n");
//			run_prog(input, envp);
//			if (ft_strncmp("nvim", input, 4) == 0)
//			{
//				printf("keyword vim found\n");
//				run_prog(input, envp);
//			}
//		}
		add_history(input);
//		printf("you shouted: %s into the void\n", input);
//		add_history(input);
//		free(input);
//		printf("the void shouts back the following:\n");
//		print_history();
//		if (ft_strrchr(input, '<'))
//		{
//			printf("%s includes a '<' character\n", input);
//		}
//		free(input);
	}

//	get_current_dir();
//	change_dir(argv[1]);
//	get_current_dir();
	return (0);
}
