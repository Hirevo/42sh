/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** turbosh
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void turbosh_prompt(shell_t *shell)
{
    char *str;

    fflush(stdout);
    printf("%s", shell->exit_code ? "\e[31;1m" : "\e[0m");
    printf("%s", "##\e[0m");
    str = getenv("LOGNAME");
    printf("\e[32;1m%s\e[0m", str ? str : "");
    printf("%s", ":");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        char *path = pretty_path(cwd);
        free(cwd);
        if (path) {
            printf("\e[34;1m%s\e[0m", path);
            free(path);
        } else {
            printf("\e[34;1m%s\e[0m", cwd);
        }
    } else {
        printf("\e[34;1m?\e[0m");
    }
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
