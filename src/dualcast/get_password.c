/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_password
*/

#include <stdlib.h>

char *get_password(void)
{
    int i;
    char *ret = calloc(5, sizeof(char));

    if (ret == NULL)
        return NULL;
    ret[4] = '\0';
    i = 0;
    while (i < 4) {
        ret[i] = (rand() % 10) + '0';
        i += 1;
    }
    return ret;
}
