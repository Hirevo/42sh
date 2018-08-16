/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** config-file
*/

#include "shell.h"
#include <stdlib.h>

void read_config(shell_t *shell)
{
    char *path = getenv("HOME");

    if (path == 0)
        return;
    
}