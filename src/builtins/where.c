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
        char *cur = path_join(lvec_at(paths, i), str);
        if (access(cur, F_OK | X_OK) == 0) {
            putstr("%s\n", cur);
            ret = 1;
        }
        free(cur);
    }
    lvec_clear(paths, true);
    lvec_drop(paths);
    return ret;
}

static int search(Shell *shell, vec_t *args, size_t i)
{
    int ret = 1;
    char *str = 0;

    if ((str = lhmap_get(shell->aliases, lvec_at(args, i)))) {
        putstr("%s is aliased to %s\n", lvec_at(args, i), str);
        ret = 0;
    }
    if ((str = lhmap_get(shell->builtins, lvec_at(args, i)))) {
        putstr("%s is a shell built-in\n", lvec_at(args, i));
        ret = 0;
    }
    char *path = getenv("PATH");
    if (path && find_cmd(path, lvec_at(args, i)))
        ret = 0;
    return ret;
}

int where_b(Shell *shell, vec_t *args)
{
    if (lvec_size(args) == 1) {
        dprintf(2, "where: too few arguments.\n");
        return 1;
    }
    for (size_t i = 1; i < lvec_size(args); i++) {
        if (is_path(lvec_at(args, i))) {
            return eputstr("where: argument is a path, not a command.\n"), 1;
        } else {
            return search(shell, args, i);
        }
    }
    return 0;
}
