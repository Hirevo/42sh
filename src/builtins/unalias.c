/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unalias
*/

#include "shell.h"

int unalias_b(shell_t *shell, vec_t *args)
{
    if (lvec_size(args) >= 2)
        return unalias(shell, args);
    else
        return eputstr("unalias: too few arguments.\n"), 1;
}
