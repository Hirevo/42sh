42sh
====

A shell written in C, the third and final shell project from EPITECH, after **minishell1** and **minishell2**.

- [Introduction](#introduction)
- [Features](#features)

Introduction
------------

The project was done as a group of 5 students:

- **Nicolas Polomack** (nicolas.polomack@epitech.eu)
- **Arthur Knoepflin** (arthur.knoepflin@epitech.eu)
- **Maxime Jenny** (maxime.jenny@epitech.eu)
- **Benjamin Solca** (benjamin.solca@epitech.eu)
- **Ludovic Leuzzi** (ludovic.leuzzi@epitech.eu)

The project was to improve upon the minishell2 (who supported at least commands with semi-colons, pipes and redirections) by adding conditionals ('&&' and '||') and the most shell features we can such as aliasing, globbing, history, auto-completion, etc...

This implementation is entirely a continuation of my minishell2 (same original codebase) because it supported a lot of features already with a somewhat maintanable code, so the group was focused on adding features to complete it.

I ensured shell and parser stability, code compatibility and could iterate on feature implementations quicker (since the shell comports code from all the way to my minishell1).  

I use the shell everyday as my default shell.  
It comports everything I need (except maybe asynchronous job control, sometimes).  
So, I am still maintaining it and will probably rewrite it eventually (in Rust, most likely).  

Features
--------

The shell launches in interactive mode by default.  
It can take a file as an argument and will execute it like a script (therefore supporting being mentioned in shebangs).  
It also accepts to evaluate a single line with **`-c`** followed by the command.  

- Delimiters:
  - Separator (**`;`**)
  - Pipes (**`|`**)
  - Redirections (**`<`**, **`>`**, **`<<`**, **`>>`**)
  - Conditionals (**`||`**, **`&&`**)
- Redirections:
  - Supports redirecting arbitrary file descriptors (by prepending it, like: **`ls not-found 2> err`**)
  - Supports specifying arbitrary file descriptors as redirection targets (like: **`ls not-found > out 2>&1`**)
  - Allows combining them with pipes (like: **`ls * 2>&1 | hexdump -C`** allows **`hexdump`** to work on both the stdout and stderr of **`ls`**)
- Quote types:
  - Double quotes: Expands variables like **`$PATH`** and **`${PATH}`**, disables file globbing such as **`*`** and **`?`**
  - Single quotes: Disables everything, even backslashes
  - Magic quotes (aka. backticks, aka. backquotes): Triggers **Command substitution**
- Line Editing:
  - Auto-completion for commands and filenames
  - Advanced line edition with cursor, arrow-keys if terminal supported, will fallback to standard stdin read otherwise
  - Variable expansions, from environment, positional arguments and built-in variables (from the **`set`** command)
  - Last exit code (**`$?`**)
  - Shell PID (**`$$`**)
  - Last argument from last command (**`$!`**)
  - Count of current positional arguments (**`$#`**)
  - Whole positional argument list, except the first one which is the script's name (**`$@`**)
  - Last argument from last command (**`$!`**)
  - Whole last command (**`!!`**)
  - N-th argument from last command (**`!:n`**)
  - File globbing with **`*`**, **`?`**, **`[a-z]`** and **`{foo,bar}`**
  - Command substitution with **`` `...` ``** and **`$(...)`**
- Aliases:
  - **`alias`** and **`unalias`** built-in commands
  - Aliases all the commands in the evaluated line
  - Self-aliasing supported
  - Alias loops are detected and prevented early
  - Aliases are saved upon exit and loaded on launch
  - Special aliases:
    - **`precmd`**: before typing a command
    - **`postcmd`**: after typing a command
    - **`cwdcmd`**: after changing directory
  - Stored in **`~/.42sh_alias`**
- History:
  - **`history`** built-in command
  - Saved in **`~/.42sh_history`**
- Environement:
  - **`env`**, **`setenv`** and **`unsetenv`** built-in commands
  - ~~**`env -i`** supported~~ Temporarily removed
  - Environment variables can be saved by writing them in **`~/.42shrc`**
- Variables:
  - **`set`** and **`unset`** built-in commands
  - Can be used for expansions
  - **`${pid}`**, **`${ppid}`**, **`${uid}`**, **`${euid}`**, **`${gid}`**, **`${pgid}`** and **`${sid}`** are set by default on launch
  - Last command's execution time in seconds (with **`${exec_duration}`**)
  - Last command's execution time human-formatted in sensible units (with **`${exec_duration_fmt}`**)
- Prompts:
  - **`prompt`** built-in command
  - 11 prompts to choose from
  - Prompt customization through the PS1 environment variable
  - Command substitution in prompts with **`\(...)`** syntax in the PS1 environment variable
  - Can be saved by setting the **`PROMPT`** environment variable with the prompt ID number
- Other built-in commands:
  - **`where`** and **`which`**
  - **`cd`**: To change directory (supports **`-`** to go back to previous directory)
  - **`exit`**: To exit the shell (supports an exit code as argument)
  - **`exec`**: Executes a command, in place of the current shell
  - **`echo`**: To print stuff (supports **`-n`**)
  - **`builtins`**: To list the available builtins
