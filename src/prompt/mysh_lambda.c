/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** mysh_lambda
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void mysh_lambda(shell_t *shell)
{
    char *git = 0;

    fflush(stdout);
    if (shell->exit_str)
        printf("\e[1m\e[38;2;255;255;85m(%s)\e[0m ", shell->exit_str);
    printf("\e[1m\e[38;2;255;85;85m42sh\e[21m\e[0m \e[1m\e[38;2;38;252;166m");
    if (shell->current != NULL)
        printf("%s", shell->current);
    printf("\e[0m \e[1m");
    git = show_cur_branch();
    if (git)
        printf("\e[1m[\e[38;2;0;133;255m%s\e[0m\e[1m] ", git);
    printf(getuid() ? "λ> " : "# ");
    fflush(stdout);
}
