/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** mysh_256
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void mysh_256(shell_t *shell)
{
    char *git = 0;

    fflush(stdout);
    if (shell->exit_str)
        printf("\e[1m\e[38;5;227m(%s)\e[0m ", shell->exit_str);
    printf("\e[1m\e[38;5;9m42sh\e[21m\e[0m \e[1m\e[38;5;48m");
    if (shell->current != NULL)
        printf("%s", shell->current);
    printf("\e[0m \e[1m");
    git = show_cur_branch();
    if (git)
        printf("\e[1m[\e[38;5;27m%s\e[0m\e[1m] ", git);
    printf(getuid() ? "$" : "#");
    printf("> ");
    fflush(stdout);
}
