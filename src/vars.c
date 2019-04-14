/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** vars
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_vars(shell_t *shell)
{
    char *str = 0;

    shell->vars = lhmap_with_capacity(4);
    if (asprintf(&str, "%d", getpid()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "pid", str);
    if (asprintf(&str, "%d", getgid()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "gid", str);
    if (asprintf(&str, "%d", getpgrp()) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "pgid", str);
    if (asprintf(&str, "%d", getsid(0)) == -1)
        handle_error("calloc");
    lhmap_set(shell->vars, "sid", str);
}
