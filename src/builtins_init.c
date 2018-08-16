/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins_init
*/

#include "shell.h"

int nb_built(const char **str)
{
    int i;

    i = 0;
    while (str[i])
        i += 1;
    return i;
}
