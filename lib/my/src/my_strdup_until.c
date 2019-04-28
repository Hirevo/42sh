/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strdup_until
*/

#include <stdlib.h>

int my_strlen_until(char *src, char sep)
{
    int i;

    i = 0;
    while (src[i] && src[i] != sep)
        i += 1;
    return (i);
}

char *my_strdup_until(char *src, char sep)
{
    int i;
    char *ret;

    if ((ret = malloc(sizeof(char) * (my_strlen_until(src, sep) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (src[i] && src[i] != sep) {
        ret[i] = src[i];
        i += 1;
    }
    ret[i] = '\0';
    return (ret);
}

int my_strlen_until_x(char *src, char sep, int repeat)
{
    int i;

    i = 0;
    while (src[i] && repeat >= 0) {
        if (src[i] == sep)
            repeat -= 1;
        if (repeat == -1)
            return (i);
        i += 1;
    }
    return (i);
}

char *my_strdup_until_x(char *src, char sep, int repeat)
{
    int i;
    char *ret;

    if ((ret = malloc(sizeof(char) *
             (my_strlen_until_x(src, sep, repeat) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (src[i] && repeat >= 0) {
        if (src[i] == sep)
            repeat -= 1;
        if (repeat >= 0) {
            ret[i] = src[i];
            i += 1;
        }
    }
    ret[i] = '\0';
    return (ret);
}
