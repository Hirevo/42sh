/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** where
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_cmd(shell_t *shell, char *str)
{
    int i;
    int ret;
    char *path = NULL;
    char *tmp;

    i = -1;
    ret = 0;
    while (shell->path[++i]) {
        if (shell->path[i][strlen(shell->path[i])] != '/')
            tmp = my_strcatdup(shell->path[i], "/");
        else
            tmp = strdup(shell->path[i]);
        if (tmp == NULL || (path = my_strcatdup(tmp, str)) == NULL)
            handle_error("calloc");
        free(tmp);
        if (access(path, F_OK | X_OK) == 0) {
            printf("%s\n", path);
            ret = 1;
        }
        free(path);
    }
    return ret;
}

static int search(shell_t *shell, int i)
{
    char *str;
    int ret;

    ret = 1;
    if ((str = get_alias_cmd(shell, shell->cur->av[i]))) {
        printf("%s is aliased to %s\n", shell->cur->av[i], str);
        free(str);
        ret = 0;
    }
    if (indexof_builtin(shell->cur->av[i]) != -1) {
        printf("%s is a shell built-in\n", shell->cur->av[i]);
        ret = 0;
    }
    if (shell->path)
        if (find_cmd(shell, shell->cur->av[i]))
            ret = 0;
    return ret;
}

int where(shell_t *shell, int args)
{
    int i;
    int ret;

    (void)args;
    i = 0;
    ret = 0;
    while (shell->cur->av[++i])
        if (is_path(shell->cur->av[i])) {
            printf("where: / in command makes no sense\n");
            ret = 1;
        }
        else
            ret |= search(shell, i);
    if (i == 1) {
        dprintf(2, "where: Too few arguments.\n");
        return 1;
    }
    return ret;
}
