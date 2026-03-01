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
### Variable setting, unsetting and expansion
Supports inherited and user defined environment variables. Use `export` to define new ones and `unset`
to remove them. A word of caution: don't `unset PATH`.
### Single and double quotes
String concatenation, variable expansion in double quotes, and no expansion in single quotes.
### Redirections
Input `<`, output (overwrite `>` and concatenation `>>`), and heredoc `<<`.
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
## Responsibilities
During development both team members made contributions to most parts of the codebase, so the lists below don't mean exclusive responsibility, but main outlines.
### Johnny Varila
- User input parsing, tokenization, string concatenation, word splitting & variable expansion
- Memory arena
- Redirections & heredocs
- Pipes
- Error handling & messages
### Ross Hvidsten
- Builtins
- Environment variable inheritance, setting & unsetting
- PATH handling
- Execution
