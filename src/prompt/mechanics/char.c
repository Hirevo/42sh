/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** char
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

void insert_char_cur(char **str, char c, int cur)
{
    int i = -1;
    char *new;

    if (*str == NULL)
        i = 0;
    else
        while ((*str)[++i])
            ;
    new = calloc(i + 2, sizeof(char));
    if (new == NULL)
        return;
    i = 0;
    while (*str && i < cur && (*str)[i]) {
        new[i] = (*str)[i];
        i += 1;
    }
    new[i] = c;
    while (*str && (*str)[i]) {
        new[i + 1] = (*str)[i];
        i += 1;
    }
    new[i + 1] = 0;
    free(*str);
    *str = new;
}

void delete_char(char **str, int cur)
{
    int i;
    int c = -1;
    char *new;

    if (*str == NULL)
        return;
    i = strlen(*str);
    if (i == 0)
        return;
    new = calloc(i, sizeof(char));
    if (new == NULL)
        handle_error("calloc");
    c = -1;
    while (++c < (cur - 1))
        new[c] = (*str)[c];
    while ((c + 1) < i) {
        new[c] = (*str)[c + 1];
        c += 1;
    }
    new[c] = 0;
    free(*str);
    *str = new;
}
