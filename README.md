# minishell
A command line interpreter using Linux system calls written in C, loosely based on Bash.
## Installation
### Prerequisites
- Linux operating system
- C compiler
- Git
- Make

Project was developed and tested on Ubuntu 22.
### Steps
1. Clone project
```sh
git clone https://github.com/zoni527/minishell.git
```
2. Change to directory
```sh
cd ./minishell
```
3. Run make
```sh
make
```
4. Run minishell
```sh
./minishell
```
## Features
### Builtins
- echo
- cd
- pwd
- exit
- export
- unset
### Variable expansion
Supports inherited and user defined environment variables.
### Single and double quotes
String concatenation, variable expansion in double quotes, and no expansion in single quotes.
### Redirections
Input `(<)`, output (overwrite `(>)` and concatenation `(>>)`), and heredoc `(<<)`.
### Piping
Chain multiple commands with `|`.
### Signals
Uses sigactions, a global signal variable, and readline hooks to catch and handle SIGINT and SIGTERM.
### Word splitting
Try:
```sh
> export o="o Hello world!"
> ech$o
```
## Concepts
- Command line
- Shell
- Bash
- Linux
- Unix
- Lexing
- Tokens
- Substitution
- Parsing
- Splitting
- Expansion
- Execution
- Redirection
- Piping
- Processes
- Files
- Directories
- Quotes
- Environment
- Environment variables
