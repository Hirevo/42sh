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
    printf("%s", shell->exit_code ? "\033[31;1m" : "\033[0m");
    printf("%s", "##\033[0m");
    str = getenv("LOGNAME");
    printf("\033[32;1m%s\033[0m", str ? str : "");
    printf("%s", ":");
    if (shell->current)
        printf("\033[34;1m%s\033[0m", shell->current);
    else
        printf("\033[34;1m?\033[0m");
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
