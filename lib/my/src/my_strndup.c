/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strndup
*/

#include "my.h"
#include <stdlib.h>

char *my_strndup(char *src, int len)
{
    char *resp;
    int count;

    count = 0;
    resp = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (resp == NULL)
        return (NULL);
    while (src[count] != '\0' && count < len) {
        resp[count] = src[count];
        count = count + 1;
    }
    resp[count] = '\0';
    return (resp);
}
