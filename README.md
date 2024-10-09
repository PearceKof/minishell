# Minishell
![42](https://img.shields.io/badge/School-42-black?style=flat-square&logo=42)

Minishell is a shell program implemented in C as part of a project at 19 (42 Network). The goal is to create a fully functional command line shell that mimics the basic functionalities of a Unix shell.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Dependencies](#dependencies)

## Project Overview

The Minishell project aims to enhance our understanding of process management, inter-process communication, and user input handling in C. The shell is designed to interpret and execute commands, manage user history, and handle various shell features while adhering to the Norm.

## Features

- Displays a prompt for user input
- Command history management
- Executes commands based on the PATH variable or relative/absolute paths
- Redirection support (input and output)
- Pipe support for chaining commands
- Environment variable expansion
- Support for special characters like `$` and `?`
- Built-in commands for shell functionality
- Proper handling of control signals (Ctrl-C, Ctrl-D, Ctrl-\)

## Requirements

- All the requirements for this project are outlined in the project description.
- Language: C, following the Norm.
- Memory Management: All allocated memory must be properly freed, and no memory leaks are tolerated.
- Makefile: The project must include a Makefile with at least the following rules: all, clean, fclean, re, and $(NAME).
- Compilation: Use `gcc` with the flags `-Wall`, `-Wextra`, and `-Werror`.
- Libft: The use of your own libft is authorized if it is included in the project directory.

## Installation

To build and run Minishell, you need a C compiler and `make`. This program is compatible with Unix-like systems.

1. Clone the repository:

```
git clone https://github.com/yourusername/minishell.git
```
```
cd minishell
```

3. Build the project:
```
make
```

4. The Makefile includes the following targets:
- `all`: Compiles the project
- `clean`: Removes object files
- `fclean`: Removes object files and the executable
- `re`: Rebuilds the project

## Usage

After building the shell, you can start it by running:

```
./minishell
```

This will open an interactive shell where you can enter commands.

## Built-in Commands

Minishell supports the following built-in commands:

- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

## Dependencies

Minishell relies solely on the C standard library and system calls. It does not require any external libraries.

