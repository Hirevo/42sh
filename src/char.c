/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** char
*/

#include <stdlib.h>

void insert_char(char **str, char c)
{
    int i = -1;
    char *new;

    if (*str == NULL)
        i = 0;
    else
        while ((*str)[++i]);
    new = calloc(i + 2, sizeof(char));
    if (new == NULL)
        return;
    i = (*str == NULL) ? 0 : -1;
    if (*str != NULL)
        while ((*str)[++i])
            new[i] = (*str)[i];
    new[i++] = c;
    new[i] = 0;
    free(*str);
    *str = new;
}

void insert_int(int **str, int c)
{
    int i = -1;
    int *new;

    if (*str == NULL)
        i = 0;
    else
        while ((*str)[++i]);
    new = calloc(i + 2, sizeof(int));
    if (new == NULL)
        return;
    i = (*str == NULL) ? 0 : -1;
    if (*str != NULL)
        while ((*str)[++i])
            new[i] = (*str)[i];
    new[i++] = c;
    new[i] = 0;
    free(*str);
    *str = new;
}
