/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** set
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_var(void *width, char *key, void *value)
{
    putstr("%*s = %s\n", (size_t)(width), key, (char *)(value));
}

size_t max(size_t a, size_t b)
{
    return (a > b) ? a : b;
}

void *max_length(void *ctx, void *acc, void *elem, size_t idx)
{
    (void)(ctx);
    (void)(idx);
    return (elem) ? (void *)(max((size_t)(acc), strlen(elem))) : acc;
}

int set_b(Shell *shell, vec_t *args)
{
    int ret = 0;

    if (lvec_size(args) == 1) {
        size_t width = (size_t)(lvec_reduce(lhmap_keys(shell->vars), max_length, 0, 0));
        lhmap_for_each(shell->vars, display_var, (void *)(width));
        return 0;
    } else {
        for (size_t i = 1; i < lvec_size(args); i++) {
            // printf("arg: '%zu'\n", strlen(lvec_at(args, 1)));
            ssize_t idx = lstr_index_of(lvec_at(args, i), 0, "=");
            if (idx == -1) {
                eputstr("set: missing value\n");
                ret = 1;
                continue;
            }
            char *key = lstr_substr(lvec_at(args, i), 0, idx);
            char *val = strdup(lvec_at(args, i) + idx + 1);
            if (key == 0 || val == 0 || check_env_error("set", key))
                ret = 1;
            else {
                free(lhmap_get(shell->vars, key));
                lhmap_set(shell->vars, key, val);
                free(key);
            }
        }
    }
    return ret;
}
