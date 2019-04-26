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

void display_var(void *ctx, char *key, void *value)
{
    (void)(ctx);
    putstr("%s\t%s\n", key, (char *)(value));
}

int set_b(Shell *shell, vec_t *args)
{
    int ret = 0;

    if (lvec_size(args) == 1) {
        lhmap_for_each(shell->vars, display_var, NULL);
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
