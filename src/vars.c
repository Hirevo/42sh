/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** vars
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void insert_line(char ***tab, char *line)
{
    char **ret;
    int size = ((*tab) == NULL) - 1;

    while ((*tab) && (*tab)[++size])
        ;
    ret = calloc(size + 2, sizeof(char *));
    if (ret == NULL)
        handle_error("calloc");
    size = ((*tab) == NULL) - 1;
    while ((*tab) && (*tab)[++size])
        ret[size] = (*tab)[size];
    ret[size] = line;
    ret[++size] = NULL;
    free(*tab);
    *tab = ret;
}

void add_var(shell_t *shell, char *name, char *value)
{
    char *str;
    char *tmp;
    int i = -1;

    if (name == NULL || (tmp = my_strcatdup(name, "\t")) == NULL)
        handle_error("calloc");
    if (value && ((str = my_strcatdup(tmp, value)) == NULL))
        handle_error("calloc");
    else if (!value)
        str = tmp;
    while (shell->vars && shell->vars[++i])
        if (!strncmp(shell->vars[i], name, strlen(name)) &&
            shell->vars[i][strlen(name)] == '\t') {
            free(shell->vars[i]);
            shell->vars[i] = (str == tmp) ? strdup(str) : str;
            return;
        }
    insert_line(&shell->vars, (str == tmp) ? strdup(str) : str);
    free(tmp);
}

char *get_var(shell_t *shell, char *name)
{
    int i = -1;
    int size;

    if (!name)
        return NULL;
    size = strlen(name);
    while (shell->vars[++i])
        if (!strncmp(shell->vars[i], name, size) &&
            shell->vars[i][size] == '\t')
            return shell->vars[i] + size + 1;
    return NULL;
}

void init_vars(shell_t *shell)
{
    char *str;

    shell->vars = NULL;
    if (asprintf(&str, "%d", getpid()) == -1)
        handle_error("calloc");
    add_var(shell, "pid", str);
    free(str);
    if (asprintf(&str, "%d", getgid()) == -1)
        handle_error("calloc");
    add_var(shell, "gid", str);
    free(str);
    if (asprintf(&str, "%d", getpgrp()) == -1)
        handle_error("calloc");
    add_var(shell, "pgid", str);
    free(str);
    if (asprintf(&str, "%d", getsid(0)) == -1)
        handle_error("calloc");
    add_var(shell, "sid", str);
    free(str);
}
