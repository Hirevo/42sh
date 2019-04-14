/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unset
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unset(shell_t *shell, int args)
{
    if (args == 1)
        return eputstr("unset: too few arguments.\n"), 1;
    for (size_t i = 0; shell->cur->av[i]; i++)
        free(lhmap_remove(shell->vars, shell->cur->av[i]));
    return 0;
}
