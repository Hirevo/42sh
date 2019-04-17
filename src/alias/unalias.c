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

int unalias(shell_t *shell, vec_t *aliases)
{
    if (shell->alias == NULL)
        return 0;
    for (size_t i = 0; i < lvec_size(aliases); ++i)
        remove_alias(shell, lvec_at(aliases, i));
    return 0;
}
