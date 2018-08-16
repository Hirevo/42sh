/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unset
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_result(char ***tab, char *line, char **ret)
{
    free(line);
    free(*tab);
    *tab = ret;
}

static void remove_line(char ***tab, char *line)
{
    int size = -1;
    int i = 0;
    char **ret;

    if (!*tab)
        return;
    while ((*tab)[++size])
        ;
    if (size == 1)
        return set_result(tab, line, NULL);
    ret = calloc(size, sizeof(char *));
    if (ret == NULL)
        handle_error("calloc");
    size = -1;
    while ((*tab)[++size]) {
        if (!strcmp((*tab)[size], line))
            continue;
        ret[i] = (*tab)[size];
        i += 1;
    }
    ret[i] = 0;
    set_result(tab, line, ret);
}

int unset(shell_t *shell, int args)
{
    int i = 0;
    int size;
    int j;

    if (args == 1) {
        dprintf(2, "unset: Too few arguments.\n");
        return 1;
    }
    while (shell->cur->av[++i]) {
        if (!shell->vars)
            return 1;
        size = strlen(shell->cur->av[i]);
        j = -1;
        while (shell->vars[++j])
            if (!strncmp(shell->vars[j], shell->cur->av[i], size) &&
                shell->vars[j][size] == '\t') {
                remove_line(&shell->vars, shell->vars[j]);
                break;
            }
    }
    return 0;
}
