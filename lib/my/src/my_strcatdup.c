/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strcatdup
*/

#include "my.h"
#include <stdlib.h>

char *my_strcatdup(char *s1, char *s2)
{
    int i;
    int j;
    char *dest;
    int len;

    i = 0;
    len = 0;
    if (s1 != NULL)
        len = my_strlen(s1);
    if ((dest = malloc(sizeof(char) * (len + my_strlen(s2) + 1))) == NULL)
        return (NULL);
    while (s1[i]) {
        dest[i] = s1[i];
        i += 1;
    }
    j = 0;
    while (s2[j]) {
        dest[i] = s2[j];
        i += 1;
        j += 1;
    }
    dest[i] = '\0';
    return (dest);
}
