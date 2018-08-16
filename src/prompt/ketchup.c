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

    fflush(stdout);
    if ((login = getenv("LOGNAME")))
        printf("\033[32;1m%s\033[0m", login);
    printf("%s", "#");
    if (shell->current)
        printf("\033[31;1m%s\033[0m", shell->current);
    else
        printf("\033[31;1m?\033[0m");
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
