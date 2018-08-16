/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** char_double
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"

char **add_to_chardouble(char *str, char **list)
{
    int i;
    char **ret = calloc(nb_args(list) + 2, sizeof(char *));

    if (ret == NULL)
        return NULL;
    ret[nb_args(list) + 1] = NULL;
    for (i = 0; list && list[i]; i++)
        ret[i] = strdup(list[i]);
    ret[i] = strdup(str);
    return ret;
}
