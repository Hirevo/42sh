/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** mysh
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void mysh(shell_t *shell)
{
    char *git = 0;

    fflush(stdout);
    printf("\e[1m\e[38;2;255;255;85m(%u)\e[0m ", shell->exit_code);
    printf("\e[1m\e[38;2;255;85;85m42sh\e[21m\e[0m \e[1m\e[38;2;38;252;166m");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        char *path = pretty_path(cwd);
        free(cwd);
        if (path) {
            printf("%s", path);
            free(path);
        } else {
            printf("%s", cwd);
        }
    } else {
        printf("?");
    }
    printf("\e[0m \e[1m");
    git = show_cur_branch();
    if (git)
        printf("\e[1m[\e[38;2;0;133;255m%s\e[0m\e[1m] ", git);
    printf(getuid() ? "$" : "#");
    printf("> ");
    fflush(stdout);
}
