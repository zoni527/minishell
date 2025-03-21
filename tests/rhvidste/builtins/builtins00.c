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

//###############################################DEFINITIONS########################################################################


char	*ft_getenv(const char *name, t_var *envp);
int	ft_setenv(char *key, char *value, t_var *envp);
t_var	*append_node(t_var *prev, char *raw, char *key, char *value);
char	*ft_getenv(const char *name, t_var *envp);
int	get_list_size(t_var *begin_list);
int	remove_env(char *key, t_var *envp);



//###############################################PROGRM FUNTIONS########################################################################

/**
 * Function to print the current directory path
 * PWD
 *
 * @param void	no input
 */
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

/**
 * Function to switch dir
 *
 * @param str	dir address to change to
 */
int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		perror("chdir() error");
		return (1);
	}
	return (0);
}

/**
 * Function to free an array
 *
 * @param arr	arr to free
 */
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

/**
 * Function to set paths for execution
 *
 * @param command	command input
 * @param mypaths	list of paths
 */
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

/**
 * Function that parses the paths for cmd execution
 *
 * @param command	command input
 * @param envp	envp_arr input (not list)
 */
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

/**
 * Function that runs execve / execution
 *
 * @param argv	argument input vector
 * @param envp	envp_arr (not list)
 */
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
/**
 * Function to run exicutable from path
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
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

/**
 * Function to remove single and double quotes from a string
 *
 * @param str	input string
 */
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
/**
 * Function to call the ECHO builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	echo(char *input, t_var *envp)
{
	(void)envp;
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

/**
 * Function to call the CD builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	cd(char *input, t_var *envp)
{
	char	*path;
	char	*old_path;
	char	*new_path;
	char	*home_path;
	char	*new_home_path;
//	(void)envp;
	old_path = getcwd(NULL, 0); // get current path to set as old path before change.
	ft_setenv("OLDPWD", old_path, envp);//set the OLD pwd enviroment variable
	path = ft_substr(input, 3, (ft_strlen(input) - 2));
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

/**
 * Function to call the EXPORT builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first element in envp list
 */
void	export(char *input ,t_var *envp)
{
	(void)envp;
	char	*raw;
	char	*key;
	char	*value;
	int	i;
	
	raw = ft_substr(input, 7, ft_strlen(input) -7);

	i = 0;
	while (raw[i] != '=')
	{
		i++;
	}
	key = ft_substr(raw, 0, i);
	value = ft_substr(raw, (i + 1), ft_strlen(raw) - (i + 1));
//	printf("key=%s\n", key);
//	printf("value=%s\n", value);
	ft_setenv(key, value, envp);
//	ft_getenv(key, envp);
//	free(raw);
//	free(key);
//	free(value);
}

/**
 * Function to call the UNSET builtin
 *
 * @param input	raw input string
 * @param envp	pointer to first envp list element
 */
void	unset(char *input, t_var *envp)
{
	(void)envp;
	char	*sub_str;

	sub_str = ft_substr(input, 6, ft_strlen(input) - 6);
	printf("unset substr = %s\n", sub_str);
	remove_env(sub_str, envp);

}

/**
 * Function to call the ENV builtin
 *
 * @param env	pinter to envp list
 */
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

//#################################################ROUTING##################################################################

/**
 * Function to check wether input is one of the builtins
 *
 * @param input	raw input to parse
 */
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

/**
 * Function to reroute to relative built in functions
 *
 * @param data	Main data struct
 * @param str	Input string
 * @param envp	Pointer to envp list
 */
void	reroute_builtin(t_minishell *data, char *str, t_var *envp)
{
	(void)data;
	if (ft_strncmp("echo", str, 4) == 0)
		echo(str, envp);
	if (ft_strncmp("cd", str, 2) == 0)
		cd(str, envp);
	if (ft_strncmp("pwd", str, 3) == 0)
		get_current_dir();
	if (ft_strncmp("export", str, 6) == 0)
		export(str, envp);
//		printf("EXPORT CALLED\n");
	if (ft_strncmp("unset", str, 5) == 0)
		unset(str, envp);
//		printf("UNSET CALLED\n");
	if (ft_strncmp("env", str, 3) == 0)
		env(envp);
//		printf("ENV CALLED");
	if (ft_strncmp("exit", str, 4) == 0)
		printf("EXIT CALLED");
	if (ft_strncmp("getenv", str, 6) == 0)
		ft_getenv(str, envp);
}


//#################################################ENVIROMENT FUNCTIONS##################################################################

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
//	t_var	*prev = NULL;
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
//	printf("list len = %d\n", list_len);
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

	//lets just check that it is working as intended
//	i = -1;
//	while (envp_arr[++i])
//	{
//		printf("%s\n", envp_arr[i]);
//	}
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
//			printf("%s\n", envar);
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
	t_var	*new_node;
	t_var	*current;
	t_var	*last;

	new_node = NULL;
	current = NULL;
	last = NULL;

	raw = ft_strjoin(key, "=");
	raw = ft_strjoin(raw, value);
//	printf("setenv raw = %s\n", raw);
	//first checking to see if the var exists, if it does then chagnes only the value
	current = envp;
	while (current)
	{
		if (strncmp(key, current->key, ft_strlen(key)) == 0)
		{
//			printf("current value exists, overwriting...\n");
			current->raw = raw;
			current->value = value;
			return (0);
		}
		last = current;
		current = current->next;
	}
	//Else if variable does not exist, then create it
//	new_node = append_node(raw, key, value);
//	if (!new_node)
//		return (1);
	if (last)
		last->next = append_node(last, raw, key, value);
//		last->next = new_node;
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
			printf("key node found\n");
			if (current->next == NULL)
			{
				current->prev->next = NULL;
				return (0);
			}
			current->next->prev = current->prev;
//			printf("current next previous is %s\n", current->prev->raw);
			current->prev->next = current->next;
			return (0);
		}
		current = current->next;
	}
	return (0);	
}

//###############################################LIST FUNTIONS########################################################################

/**
 * Function that returns the length of a list
 *
 * @param begin_list	pointer to the beginning of the list
 */
int	get_list_size(t_var *begin_list)
{
	if (begin_list == 0)
		return (0);
	else
		return (1 + get_list_size(begin_list->next));
}

/**
 * Function that frees the enviroment list
 *
 * @param head	pointer to the head of the list
 */
void	free_list(t_var *head)
{
	while(head)
	{
		t_var *temp = head;
		free(temp->raw);
		free(temp->key);
		free(temp->value);
		head = head->next;
		free(temp);
	}
}

/**
 * Function that prints env from
 * linked list
 *
 * @param list	list to print contents of
 */
void	print_env_list(t_var *list)
{
	t_var *current = list;
	while (current)
	{
		printf("%s\n", current->raw);
		current = current->next;
	}
}

/**
 * Function appends node and adds values
 * variable it finds.
 *
 * @param data	Main data struct
 * @param raw	Raw input
 * @param key	Key input
 * @param value	Value input
 */
t_var	*append_node(t_var *prev, char *raw, char *key, char *value)
{
	t_var *new_node = (t_var *)malloc(sizeof(t_var));
	new_node->raw = raw;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = prev;
	return (new_node);
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
	char	**envp_arr;
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
			reroute_builtin(&data, input, data.custom_env);
		}
		else
		{
			envp_arr = convert_envp_to_arr(data.custom_env);
			run_prog(input, envp_arr);
		}
		add_history(input);
	}
	free_list(data.custom_env);
	return (0);
}
