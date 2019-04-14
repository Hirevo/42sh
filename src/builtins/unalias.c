/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unalias
*/

#include "shell.h"

int unalias_b(shell_t *shell, int args)
{
    if (args >= 2)
        return unalias(shell, shell->cur->av + 1);
    else
        return eputstr("unalias: too few arguments.\n"), 1;
}
