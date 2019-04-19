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

int unset_b(shell_t *shell, vec_t *args)
{
    if (lvec_size(args) == 1)
        return eputstr("unset: too few arguments.\n"), 1;
    for (size_t i = 1; i < lvec_size(args); i++)
        free(lhmap_remove(shell->vars, lvec_at(args, i)));
    return 0;
}
