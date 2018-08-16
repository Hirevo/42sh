# 42sh

A shell written in C, the third and final shell project from EPITECH, after **minishell1** and **minishell2**.

## Introduction

The project was done in a group of 5 students:
- **Nicolas Polomack** (nicolas.polomack@epitech.eu)
- **Arthur Knoepflin** (arthur.knoepflin@epitech.eu)
- **Maxime Jenny** (maxime.jenny@epitech.eu)
- **Benjamin Solca** (benjamin.solca@epitech.eu)
- **Ludovic Leuzzi** (ludovic.leuzzi@epitech.eu)

The project was to improve upon the minishell2 (who supported at least commands with semi-colons, pipes and redirections) by adding conditionals ('&&' and '||') and the most shell features we can such as aliasing, globbing, history, auto-completion, etc...

This implementation is entirely a continuation of my minishell2 (same original codebase) because it supported a lot of features already with a somewhat maintanable code, so the group was focused on adding features to complete it.

I ensured shell and parser stability, code compatibility and could iterate on feature implementations quicker (since the shell comports code from all the way to my minishell1).  

I use the shell everyday as my default shell.  
It comports everything I need (except maybe job control, sometimes).  
So, I am still maintaining it and will probably rewrite it eventually (in Rust, most likely).  

## Features

The shell launches in interactive mode by default.  
It can take a file as an argument and will execute it like a script (therefore supporting being mentioned in shebangs).  
It also accept to evaluate a single line with **`-c`** followed by the command.  

- Delimiters:
    - Separator (**`;`**)
    - Pipes (**`|`**)
    - Redirections (**`<`**, **`>`**, **`<<`**, **`>>`**)
    - Conditionals (**`||`**, **`&&`**)
- Quote types:
    - Double quotes (Expands variables like **`$PATH`**, disables file globbing such as **`*`** and **`?`**)
    - Single quotes (Disables everything except escaping with backslashes)
    - Magic quotes / Back ticks (Evaluates the sub-command and replace with the results in-place)
- Line Editing:
    - Auto-completion for commands and filenames
    - Advanced line edition with cursor, arrow-keys if terminal supported, will fallback to standard stdin read otherwise
    - Variable expansions, from environment and built-in variables (from the **`set`** command)
    - Last exit code (**`$?`**)
    - Shell PID (**`$$`**)
    - Last argument from last command (**`$!`**)
    - Whole last command (**`!!`**)
    - n-th argument from last command (**`!:n`**)
    - File globbing with **`*`**, **`?`**, **`[a-z]`** and **`{foo,bar}`**
- Aliases:
    - **`alias`** and **`unalias`** built-in commands
    - Aliases all the commands in the evaluated line
    - Self-aliasing supported
    - Alias loops are detected and prevented
    - Aliases are saved upon exit and loaded on launch
    - Stored in **`~/.42sh_alias`**
- History:
    - **`history`** built-in command
    - Saved in **`~/.42sh_history`**
- Environement:
    - **`env`**, **`setenv`** and **`unsetenv`** built-in commands
    - **`env -i`** supported
    - Environment variables can be saved by writing them in **`~/.42shrc`**
- Variables:
    - **`set`** and **`unset`** built-in commands
    - Can be used for expansions
    - **`$pid`**, **`$sid`**, **`$gid`** and **`$pgid`** are set by default on launch
- Prompts:
    - **`prompt`** built-in command
    - 7 prompts to choose from
    - Can be saved by setting the **`PROMPT`** environment variable with the prompt ID number
- Other built-in commands:
    - **`where`** and **`which`**
    - **`cd`**: To change directory (supports **`-`** to go back to previous directory)
    - **`exit`**: To exit the shell (supports an exit code as argument)
    - **`echo`**: To print stuff (supports **`-n`**)
    - **`builtins`**: To list the builtins available
