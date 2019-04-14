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
    printf("\e[1m\e[38;5;227m(%u)\e[0m ", shell->exit_code);
    printf("\e[1m\e[38;5;9m42sh\e[21m\e[0m \e[1m\e[38;5;48m");
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
        printf("\e[1m[\e[38;5;27m%s\e[0m\e[1m] ", git);
    printf(getuid() ? "$" : "#");
    printf("> ");
    fflush(stdout);
}
