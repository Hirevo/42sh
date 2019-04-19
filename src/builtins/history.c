/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** history
*/

#include "shell.h"

int history_b(shell_t *shell, vec_t *args)
{
    (void)(args);
    for (size_t i = 1; i < lvec_size(shell->hist.arr); i++) {
        char **payload = lvec_at(shell->hist.arr, i);
        putstr("%6lu\t", i);
        for (size_t j = 0; payload[j]; j++)
            putstr(i ? " %s" : "%s", payload[j]);
        putstr("\n");
    }
    return 0;
}
