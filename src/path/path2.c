/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** path2
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

char **set_default_path(void)
{
    char **path = calloc(3, sizeof(char *));

    if (path == NULL)
        handle_error("calloc");
    path[0] = strdup("/bin");
    path[1] = strdup("/usr/bin");
    return path;
}
