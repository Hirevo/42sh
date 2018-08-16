/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** tcsh
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void tcsh_prompt(shell_t *shell)
{
    char *hostname;

    fflush(stdout);
    if ((hostname = get_hostname()))
        printf("\e[4m%s\e[0m", hostname);
    free(hostname);
    printf("%s", ":");
    if (shell->current)
        printf("\e[1m%s\e[0m", shell->current);
    else
        printf("\e[1m?\e[0m");
    printf("%s", "> ");
    fflush(stdout);
}
