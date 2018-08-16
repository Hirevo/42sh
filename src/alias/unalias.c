/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unalias
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

void remove_alias(shell_t *shell, char *alias)
{
    free(lhmap_remove(shell->alias, alias));
}

int unalias(shell_t *shell, char **aliases)
{
    int i;

    i = -1;
    if (shell->alias == NULL)
        return 0;
    while (aliases[++i])
        remove_alias(shell, aliases[i]);
    return 0;
}
