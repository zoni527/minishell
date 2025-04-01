# Errors

Notes about bash errors, error message types and error precedence for minishell

## Types of errors

A list of error types and reasons behind error messages
(some errors might share the same message)

- A file or directory doesn't exist
- Permissions are incorrect for file execution
- Permissions are incorrect for file access
- Permissions are incorrect for file creation
- Something is a directory when it shouldn't be
- Something is not a directory when it should be
- Something is not a directory, even when it doesn't need to be
- Syntax errors
    - Unexpected token

minishell specific:

- Unclosed quotes

## Bash error message examples

```
$ not_a_command
> not_a_command: command not found

$ cat/
> bash: cat/: No such file or directory

$ /usr/bin/cat/
> bash: /usr/bin/cat: Not a directory

$ /usr/bin
> bash: /usr/bin: Is a directory

$ /usr/bin/
> bash: /usr/bin/: Is a directory

$ /root/doesnt_exist
> bash: /root/doesn_exist: Permission denied
```
