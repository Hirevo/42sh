/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** bash
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bash_prompt(shell_t *shell)
{
    char *login = getenv("LOGNAME");
    char *hostname = get_hostname();

    fflush(stdout);
    if (login && hostname) {
        printf("\033[32;1m%s@%s\033[0m", login, hostname);
        free(hostname);
    }
    printf("%s", ":");
    if (shell->current)
        printf("\033[34;1m%s\033[0m", shell->current);
    else
        printf("\033[34;1m?\033[0m");
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
