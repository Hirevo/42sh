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

static int find_cmd(const char *path, char *str)
{
    int ret = 0;
    vec_t *paths = lstr_split(path, ":");

    for (size_t i = 0; i < lvec_size(paths); i++) {
        char *cur = path_join(path, str);
        if (access(cur, F_OK | X_OK) == 0) {
            printf("%s\n", cur);
            ret = 1;
        }
        free(cur);
    }
    lvec_clear(paths, true);
    lvec_drop(paths);
    return ret;
}

static int search(shell_t *shell, int i)
{
    int ret = 1;

    char *str = get_alias_cmd(shell, shell->cur->av[i]);
    if (str) {
        printf("%s is aliased to %s\n", shell->cur->av[i], str);
        free(str);
        ret = 0;
    }
    if (indexof_builtin(shell->cur->av[i]) != -1) {
        printf("%s is a shell built-in\n", shell->cur->av[i]);
        ret = 0;
    }
    char *path = getenv("PATH");
    if (path && find_cmd(path, shell->cur->av[i]))
        ret = 0;
    return ret;
}

int where(shell_t *shell, int args)
{
    if (args == 1) {
        dprintf(2, "where: too few arguments.\n");
        return 1;
    }
    for (size_t i = 1; shell->cur->av[i]; i++) {
        if (is_path(shell->cur->av[i])) {
            return eputstr("where: argument is a path, not a command.\n"), 1;
        } else {
            return search(shell, i);
        }
    }
    return 0;
}
