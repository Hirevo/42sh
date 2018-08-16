/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

int set_env(char *name, char *value)
{
    if (check_env_error("setenv", name))
        return 1;
    return (!setenv(name, value, 1)) ? 0 : -1;
}

int unset_env(char **names)
{
    int ret;
    int i;

    ret = 0;
    i = 0;
    while (names[++i])
        ret |= unsetenv(names[i]);
    return ret;
}
