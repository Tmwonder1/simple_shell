# Simple Shell

Simple Shell is a basic Unix shell written in C. It provides a command line interface for user interaction, allowing users to execute commands found in the PATH or specify programs with a path. This shell supports job control, command history, and basic I/O redirection.

## Features

- **Command Execution**: Execute all UNIX commands available in the PATH or via absolute paths.
- **Input/Output Redirection**: Redirect command input and output to and from files.
- **Piping**: Pipe the output of one command as the input to another.
- **Job Control**: Basic foreground and background job controls using `&`, `fg`, and `bg`.
- **Command History**: Navigate through previously entered commands.

## Getting Started

### Prerequisites

Ensure you have GCC installed to compile the shell program. To check if GCC is installed, you can run:

```bash
gcc --version