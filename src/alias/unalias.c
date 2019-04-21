/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unalias
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

void remove_alias(Shell *shell, char *alias)
{
    free(lhmap_remove(shell->aliases, alias));
}

int unalias(Shell *shell, vec_t *aliases)
{
    if (shell->aliases == NULL)
        return 0;
    for (size_t i = 0; i < lvec_size(aliases); ++i)
        remove_alias(shell, lvec_at(aliases, i));
    return 0;
}
