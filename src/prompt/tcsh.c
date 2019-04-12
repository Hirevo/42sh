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
    OPTION(CharPtr) hostname = get_hostname();

    fflush(stdout);
    printf("\e[4m%s\e[0m", OPT_UNWRAP_OR(hostname, "???"));
    OPT_AND_THEN(hostname, free);
    printf("%s", ":");
    if (shell->current)
        printf("\e[1m%s\e[0m", shell->current);
    else
        printf("\e[1m???\e[0m");
    printf("%s", "> ");
    fflush(stdout);
}
