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

# include "include/minishell.h"

//###############################################LIST FUNTIONS########################################################################




//###############################################PROGRM FUNTIONS########################################################################

// Function to print the current directory path
int	get_current_dir(void)
{
	char	*buffer = getcwd(NULL, 0); // Dynamically allocate memory
	
	if (buffer != NULL)
	{
		printf("%s\n", buffer);
		free (buffer);
	}
	else
	{
		perror("getcwd error");
		return (1);
	}
	return (0);
}

// FUnction to switch dir
int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}

//Function to free an array
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

//###############################################PROGRAM EXECUTION(taken from pipex)############################################
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

//#########################################################################################################################
// Function to run executibal from path.
int	run_prog(char *input, char **envp)
{
	(void)input;
//	(void)envp;
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

////Function to remove single and double quotes from a string
//char	*remove_quotes(char *str)
//{
//	int	i;
//	int	j;
//	int	count;
//	char	*dest;
//
//	count = 0;
//	i = -1;
//	j = 0;
//	while (str[++i])
//	{
//		if (str[i] == '"' || str[i] == '\'')
//			count++;
//	}
//	dest = malloc(sizeof(char) * (i - count) + 1);
//	if (dest == NULL)
//		return (NULL);
//	i = -1;
//	while(str[++i])
//	{
//		if (str[i] != '"' && str[i] != '\'')
//			dest[j++] = str[i];
//	}
//	dest[j] = '\0';
//	return (dest);
//}

//*note: This is for debugging perposes and should be removed.
// Function to get specific env variable.
char	*ft_getenv(const char *name, char **envp)
{
	(void)envp;
	char	*sub_name;
	char	*envar;
	//getenv
	if (ft_strncmp(name, "getenv", 6) == 0)
	{
		sub_name = ft_substr(sub_name, 7, ft_strlen(name) - 6);
	}
	else
	{
		sub_name = ft_strdup(name);
	}
	printf("sub_name = %s\n", sub_name);
	envar = getenv(sub_name);
	printf("envar = %s\n", envar);
	free(sub_name);
	return (envar);
}	

////Function to set enviroment variable value.
//int	ft_setenv(const char *name, const char *value, char **envp)
//{
//	int	i;
//	size_t len;
//	char *new_var;
//
//	len = ft_strlen(name);
//
//	//Search for existing variable
//	i = -1;
//	while (envp[++i])
//	{
//		//If variable found, replace it
//		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
//		{
//			new_var = malloc(len + ft_strlen(value) + 2);
//			if (!new_var)
//				return (-1);
//			free(envp[i]);
//			envp[i] = new_var;
////			free(new_var);
////			printf("%s=%s\n", name, value);
//			return (0);
//		}
//	}
//	//if Variable not found, add a new enrty
//	new_var = malloc(len + ft_strlen(value) + 2);
//	if (!new_var)
//		return (-1);
//	envp[i] = new_var;
//	envp[i + 1] = NULL;
////	free(new_var);
////	printf("%s=%s\n", name, value);
//	return (0);
//}

// Function to set enviroment variable
int	ft_setenv(const char *name, const char *value, char **envp)
{
	int		i;
	size_t	name_len;
	size_t	value_len;
	char	*new_var;
	char	*new_str1;
//	char	*new_str2;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);

	i = -1;
	while (envp[++i])
	{
		// if variable already exists
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
		{
			new_var = malloc(name_len + value_len + 2); // +2 for '=' and '\0'
			if (!new_var)
			{
				perror("malloc failed");
				return (-1);
			}
			new_str1 = ft_strjoin(name, "=");
			new_var = ft_strjoin(new_str1, value);
			printf("new_var = %s\n", new_var);
			envp[i] = new_var;
			printf("envp[%d] = %s\n", i, envp[i]);

			return (0);
		}
	}
	return (1);
}

//Function to remove single and double quotes from a string
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

//################################################BUILT INS###########################################################################
// Function to run ECHO builtin
void	echo(char *input)
{
	char	*sub_str;
	char	*n_str;
	char	*no_quotes;
	sub_str = ft_substr(input, 5, ft_strlen(input) - 4);
//	printf("substr is %s\n", sub_str);
	if (sub_str[0] == '-' && sub_str[1] == 'n')
	{
//		printf("-n flag detected\n");
		n_str = ft_substr(sub_str, 3, ft_strlen(sub_str) -2);
//		printf("n_string:%s\n", n_str);
		no_quotes = remove_quotes(n_str);
		free(n_str);
		ft_putstr_fd(no_quotes, 1);
		free(no_quotes);
	}
	else
	{
//		printf("no -n flag detected\n");
		no_quotes = remove_quotes(sub_str);
		ft_putendl_fd(no_quotes, 1);
		free(no_quotes);
	}
	free(sub_str);
}

//Function to run CD builtin
void	cd(char *input, char **envp)
{
	char	*path;
	char	*old_path;
	char	*new_path;
	char	*home_path;
	char	*new_home_path;
	(void)envp;

	old_path = getcwd(NULL, 0); // get current path to set as old path before change.
	ft_setenv("OLDPWD", old_path, envp);//set the OLD pwd enviroment variable
	path = ft_substr(input, 3, (ft_strlen(input) - 2));

//	printf("path = %s\n", path);
	if (path[0] == '~')
	{
		new_path = ft_substr(path, 1, (ft_strlen(path) - 1));
//		printf("path == '~'\n");
		home_path = getenv("HOME");
//		printf("newpath = %s%s\n", home_path, new_path);
		new_home_path = ft_strjoin(home_path, new_path);
		change_dir(new_home_path);
		ft_setenv("PWD", new_home_path, envp);
		free(new_home_path);
		free(new_path);
	}
	//Here we check is CD is just added on its own.
	else if (path[0] == '\0')
	{
//		printf("CD COMMAND ENTERED\n");
		home_path = getenv("HOME");
		ft_setenv("PWD", home_path, envp);
		change_dir(home_path);
	}
	else
	{
//		printf("cd detected\n");
		change_dir(path);
		new_path = getcwd(NULL, 0);
		ft_setenv("PWD", new_path, envp);
	}
	free(path);
}

// Function to call the EXPORT builtin
void	export(char *input ,char **envp)
{
	(void)envp;
	char	*sub_str;
	char	*name;
	char	*value;
	int	i;
	
	sub_str = ft_substr(input, 7, ft_strlen(input) -7);

	i = 0;
	while (sub_str[i] != '=')
	{
		i++;
	}

	name = ft_substr(sub_str, 0, i);
	value = ft_substr(sub_str, (i + 1), ft_strlen(sub_str) - (i + 1));
	printf("name=%s\n", name);
	printf("value=%s\n", value);
	ft_setenv(name, value, envp);
	ft_getenv(name, envp);
	free(sub_str);
	free(name);
	free(value);
}

// Function to call the ENV building
void	env(t_var *env)
{
	t_var	*current;
	current = env;
	while (current)
	{
		ft_putendl_fd(current->raw, 1);
		current = current->next;
	}
}

//// Function to call the ENV builtin
//void	env(char **envp)
//{
//	int	i;
//	i = -1;
//	while (envp[++i])
//	{
//		ft_putendl_fd(envp[i], 1);
//	}
//}

//#################################################ROUTING##################################################################
// Function to check wether its one of the builtins.
int	check_if_builtin(char *input)
{
	if (ft_strncmp("echo", input, 4) == 0)
		return (0);
	if (ft_strncmp("cd", input, 2) == 0)
		return (0);
	if (ft_strncmp("pwd", input, 3) == 0)
		return (0);
	if (ft_strncmp("export", input, 6) == 0)
		return (0);
	if (ft_strncmp("unset", input, 5) == 0)
		return (0);
	if (ft_strncmp("env", input, 3) == 0)
		return (0);
	if (ft_strncmp("exit", input, 4) == 0)
		return (0);
	if (ft_strncmp("getenv", input, 6) == 0)
		return (0);
	return (1);
}

// Function to reroute to relative built in functions
void	reroute_builtin(t_minishell *data, char *str, char **envp)
{
	if (ft_strncmp("echo", str, 4) == 0)
		echo(str);
	if (ft_strncmp("cd", str, 2) == 0)
		cd(str, envp);
	if (ft_strncmp("pwd", str, 3) == 0)
		get_current_dir();
	if (ft_strncmp("export", str, 6) == 0)
		export(str, envp);
//		printf("EXPORT CALLED\n");
	if (ft_strncmp("unset", str, 5) == 0)
		printf("UNSET CALLED\n");
	if (ft_strncmp("env", str, 3) == 0)
		env(data->custom_env);
//		printf("ENV CALLED");
	if (ft_strncmp("exit", str, 4) == 0)
		printf("EXIT CALLED");
	if (ft_strncmp("getenv", str, 6) == 0)
		ft_getenv(str, envp);
}

void	print_env_list(t_var *list)
{
//	t_var	*list;
//	list = data->custom_env;
//	printf("list1 = %s\n", list->key);
	t_var *current = list;
	while (current)
	{
		printf("%s\n", current->raw);
		current = current->next;
	}
}

t_var	*append_node(t_minishell *data, char *raw, char *key, char *value)
{
	(void)data;
	t_var *new_node = (t_var *)malloc(sizeof(t_var));
	new_node->raw = raw;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

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
//		printf("%s\n", raw);
		j = 0;
		while (raw[j] != '=')
		{
			j++;
		}
		key = ft_substr(raw, 0, j);
		value = ft_substr(raw, (j + 1), ft_strlen(raw) - (j + 1));
		
		if (head == NULL)
		{
			head = append_node(data, raw, key, value);
			current = head;
			data->custom_env = head;
//			printf("head raw = %s\n", data->custom_env->raw);
//			free(raw);
//			free(key);
//			free(value);
		}
		else
		{
			current->next = append_node(data, raw, key, value);
			current = current->next;
//			printf("current raw = %s\n", current->raw);
//			free(raw);
//			free(key);
//			free(value);
		}
	}
//	data.custom_env = &(t_var){.raw = "ARG=test test", .key = "ARG", .value = "|test|"};
//	data.custom_env->next = &(t_var){.raw = "", .key = "DERP", .value = "|derp|"};
}

//############################################MAIN#############################################################################
int	main(int argc, char **argv, char **envp)
{
	static t_minishell	data;
	(void)argc;
	(void)argv;
//	(void)data;
//	(void)envp;
	char	*input;
	char	*shell_dir;
	char	*buffer;
//
	//first parsing the enviroment variables into a linked list
	parse_env(&data, envp);
//	printf("data_test = %s\n", data.custom_env->raw);
//	print_env_list(data.custom_env);

	while (1)
	{	
		buffer = getcwd(NULL, 0); // gets the current dir
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
		if (check_if_builtin(input) == 0)
		{
//			printf("buildin detected\n");
			reroute_builtin(&data, input, envp);
		}
		else
		{
			run_prog(input, envp);
		}
		add_history(input);
	}
	return (0);
}
