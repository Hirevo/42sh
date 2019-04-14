/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ketchup
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void ketchup_prompt(shell_t *shell)
{
    char *login;

    (void)(shell);
    fflush(stdout);
    if ((login = getenv("LOGNAME")))
        printf("\e[32;1m%s\e[0m", login);
    printf("%s", "#");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        char *path = pretty_path(cwd);
        free(cwd);
        if (path) {
            printf("\e[31;1m%s\e[0m", path);
            free(path);
        } else {
            printf("\e[31;1m%s\e[0m", cwd);
        }
    } else {
        printf("\e[31;1m?\e[0m");
    }
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
