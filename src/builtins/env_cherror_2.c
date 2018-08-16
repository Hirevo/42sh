/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env_cherror_2
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"

static int is_valid(char *str)
{
    for (int i = 0; str[i]; i++)
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') ||
                (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            return 0;
    return 1;
}

int is_alpha_err(char *lines, int size)
{
    if (!is_valid(lines + size)) {
        dprintf(2, "env: cannot unset '%s': Invalid argument\n", lines + size);
        return 1;
    }
    return 0;
}
