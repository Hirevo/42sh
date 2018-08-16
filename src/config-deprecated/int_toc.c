/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** int_toc
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

int size_int(int nb)
{
    int i = 0;

    if (nb == 0)
        return 1;
    while (nb != 0) {
        nb = nb / 10;
        i += 1;
    }
    return i;
}

char *toc_alloc(int nb)
{
    char *ret;

    if (nb < 0) {
        ret = calloc(size_int(nb) + 2, sizeof(char));
        if (ret == NULL)
            handle_error("calloc");
        ret[0] = '-';
        nb *= (-1);
    }
    else {
        ret = calloc(size_int(nb) + 1, sizeof(char));
        if (ret == NULL)
            handle_error("calloc");
    }
    return ret;
}

char *int_toc(int nb)
{
    int i[2] = {1, size_int(nb)};
    char *ret = toc_alloc(nb);

    if (nb < 0) {
        nb *= (-1);
        ret[size_int(nb) + 1] = '\0';
    }
    else {
        i[1] -= 1;
        ret[size_int(nb)] = '\0';
    }
    while (i[0] <= size_int(nb)) {
        ret[i[1]] = (nb / my_power_rec(10, i[0] - 1) % 10) + 48;
        i[1] -= 1;
        i[0] += 1;
    }
    if (nb == 0)
        ret[0] = '0';
    return ret;
}
