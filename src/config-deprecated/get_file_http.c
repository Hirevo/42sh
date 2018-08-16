/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_file_http
*/

#include "my.h"
#include "server.h"
#include <stdlib.h>
#include <string.h>

char *special_case(char *ret)
{
    if (!strcmp(ret, "/")) {
        free(ret);
        return strdup("/index.html");
    }
    if (!strcmp(ret, "/help")) {
        free(ret);
        return strdup("/help.html");
    }
    if (!strcmp(ret, "/privacy")) {
        free(ret);
        return strdup("/privacy.html");
    }
    return NULL;
}

char *get_file_http(char *buf)
{
    char *ret;
    char *spec;
    int i;

    if (my_strncmp(buf, "GET", 3))
        return NULL;
    buf += 4;
    i = 0;
    while (buf[i] && buf[i] != ' ')
        i += 1;
    ret = my_strndup(buf, i);
    if ((spec = special_case(ret)) != NULL)
        return spec;
    return ret;
}
