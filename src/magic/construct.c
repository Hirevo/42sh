/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** construct
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *construct_magic(char **tab)
{
    int i = -1;
    int len = 0;
    char *ret;

    while (tab[++i])
        len += ((!!i) + strlen(tab[i]) + 2);
    ret = calloc(len + 1, sizeof(char));
    if (ret == NULL)
        handle_error("calloc");
    i = -1;
    while (tab[++i]) {
        if (i)
            strcat(ret, " ");
        strcat(ret, tab[i]);
    }
    return ret;
}
