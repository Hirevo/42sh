/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** load_file
*/

#include "get_next_line.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

void free_tab(char **tab)
{
    int i = 0;

    while (tab && tab[i]) {
        free(tab[i]);
        i += 1;
    }
    free(tab);
}

int nb_tab(char **tab)
{
    int i = 0;

    while (tab && tab[i])
        i += 1;
    return i;
}

static char **add_line(char **actual, char *line)
{
    int i = 0;
    char **ret = calloc(nb_tab(actual) + 2, sizeof(char *));

    if (ret == NULL)
        return NULL;
    ret[nb_tab(actual) + 1] = NULL;
    while (actual && actual[i]) {
        ret[i] = strdup(actual[i]);
        free(actual[i]);
        i += 1;
    }
    ret[i] = line;
    free(actual);
    return ret;
}

char **load_file(int fd)
{
    char *line = get_next_line(fd);
    char **ret = 0;

    while (line) {
        ret = add_line(ret, line);
        if (ret == NULL)
            return NULL;
        line = get_next_line(fd);
    }
    return ret;
}
