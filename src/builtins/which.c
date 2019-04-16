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
            printf("%s\n", cur);
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

static int search(shell_t *shell, int i)
{
    char *str;
    int ret = 1;

    ret = 1;
    if ((str = get_alias_cmd(shell, shell->cur->av[i]))) {
        printf("%s: \t aliased to %s\n", shell->cur->av[i], str);
        free(str);
        ret = 0;
    }
    if (ret && indexof_builtin(shell->cur->av[i]) != -1) {
        printf("%s: shell built-in command.\n", shell->cur->av[i]);
        ret = 0;
    }
    char *path = getenv("PATH");
    if (ret && path && find_first_cmd(path, shell->cur->av[i]))
        ret = 0;
    if (ret == 1)
        printf("%s: command not found.\n", shell->cur->av[i]);
    return ret;
}

int which(shell_t *shell, int args)
{
    if (args == 1) {
        dprintf(2, "which: too few arguments.\n");
        return 1;
    }
    for (size_t i = 1; shell->cur->av[i]; i++) {
        if (is_path(shell->cur->av[i])) {
            if (access(shell->cur->av[i], F_OK | X_OK) == 0) {
                printf("%s\n", shell->cur->av[i]);
                return 0;
            } else {
                printf("%s: command not found.\n", shell->cur->av[i]);
                return 1;
            }
        } else {
            return search(shell, i);
        }
    }
    return 0;
}
