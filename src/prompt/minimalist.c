/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** minimalist
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void minimalist_prompt(Shell *shell)
{
    char *user;

    fflush(stdout);
    (void)shell;
    if ((user = getenv("LOGNAME")))
        printf("%s) ", user);
    else
        printf(") ");
    fflush(stdout);
}
