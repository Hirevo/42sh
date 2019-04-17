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

int unset_env(vec_t *names)
{
    int ret = 0;

    for (size_t i = 1; i < lvec_size(names); i++)
        ret |= unsetenv(lvec_at(names, i));
    return ret;
}
