/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** which
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_first_cmd(const char *path, char *str)
{
    vec_t *paths = lstr_split(path, ":");

    for (size_t i = 0; i < lvec_size(paths); i++) {
        char *cur = path_join(lvec_at(paths, i), str);
        if (access(cur, F_OK | X_OK) == 0) {
            putstr("%s\n", cur);
            lvec_clear(paths, true);
            lvec_drop(paths);
            return 1;
        }
        free(cur);
    }
    lvec_clear(paths, true);
    lvec_drop(paths);
    return 0;
}

static int search(shell_t *shell, vec_t *args, size_t i)
{
    char *str;
    int ret = 1;

    ret = 1;
    if ((str = lhmap_get(shell->aliases, lvec_at(args, i)))) {
        putstr("%s: aliased to %s.\n", lvec_at(args, i), str);
        ret = 0;
    }
    if ((str = lhmap_get(shell->builtins, lvec_at(args, i)))) {
        putstr("%s: shell built-in command.\n", lvec_at(args, i));
        ret = 0;
    }
    char *path = getenv("PATH");
    if (ret && path && find_first_cmd(path, lvec_at(args, i)))
        ret = 0;
    if (ret == 1)
        eputstr("%s: command not found.\n", lvec_at(args, i));
    return ret;
}

int which_b(shell_t *shell, vec_t *args)
{
    if (lvec_size(args) == 1) {
        dprintf(2, "which: too few arguments.\n");
        return 1;
    }
    for (size_t i = 1; lvec_at(args, i); i++) {
        if (is_path(lvec_at(args, i))) {
            if (access(lvec_at(args, i), F_OK | X_OK) == 0) {
                putstr("%s\n", lvec_at(args, i));
                return 0;
            } else {
                eputstr("%s: command not found.\n", lvec_at(args, i));
                return 1;
            }
        } else {
            return search(shell, args, i);
        }
    }
    return 0;
}
