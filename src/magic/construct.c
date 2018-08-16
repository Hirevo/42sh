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

int count_separators(char *str)
{
    int i = -1;
    int count = 0;

    while (str[++i])
        if (str[i] == '\\')
            i += !!(str[i + 1]);
        else if (is_separator(str[i]) || is_space(str[i]) || str[i] == '\\' ||
            str[i] == '"' || str[i] == '\'')
            count += 1;
    return count;
}

char *sanitize(char *str, int to_free)
{
    int i1 = -1;
    int i2 = 0;
    int size = count_separators(str);
    char *ret = calloc(strlen(str) + (size * 2) + 1, sizeof(char));

    if (ret == NULL)
        return NULL;
    while (str[++i1])
        if (str[i1] == '\\' || is_separator(str[i1]) || str[i1] == '"' ||
            str[i1] == '\'' || is_space(str[i1])) {
            ret[i2++] = '\\';
            ret[i2++] = str[i1];
        }
        else
            ret[i2++] = str[i1];
    ret[i2] = 0;
    if (to_free)
        free(str);
    return ret;
}

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
