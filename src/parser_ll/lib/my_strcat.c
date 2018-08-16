/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** my_strcat
*/

#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bs_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;
    char *str = calloc(strlen(dest) + strlen(src) + 1, sizeof(char));

    if (str)
        return NULL;
    while (dest[i] != '\0') {
        str[i] = dest[i];
        i++;
    }
    while (src[j] != '\0') {
        str[i] = src[j];
        i++;
        j++;
    }
    str[i] = '\0';
    free(dest);
    return str;
}
