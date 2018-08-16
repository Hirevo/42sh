/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** com_sock
*/

#include "my.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *concat_com(char *str1, char *str2, int size)
{
    int i = 0;
    int j = 0;
    int len = (str1 == NULL) ? size : strlen(str1) + size;
    char *ret = calloc(len + 1, sizeof(char));

    if (ret == NULL)
        return NULL;
    while (str1 && str1[i]) {
        ret[i] = str1[i];
        i += 1;
    }
    while (j < size) {
        ret[i] = str2[j];
        i += 1;
        j += 1;
    }
    ret[i] = '\0';
    return ret;
}

int read_socket(t_socket sock, char **ret)
{
    char tmp[SIZE_SOCK];
    size_t len = recv(sock, tmp, SIZE_SOCK, 0);

    *ret = NULL;
    while (len == SIZE_SOCK)
        *ret = concat_com(*ret, tmp, len);
    *ret = concat_com(*ret, tmp, len);
    return strlen(*ret);
}

void write_socket(t_socket sock, char *str)
{
    if (str) {
        if (send(sock, str, strlen(str), 0) < 0)
            perror("send");
    }
}
