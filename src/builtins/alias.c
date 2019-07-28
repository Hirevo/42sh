/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** alias
*/

#include "shell.h"

static void *join_strings(void *ctx, void *acc, void *elem, size_t idx)
{
    (void)(ctx);
    if (idx < 2) {
        return 0;
    } else if (acc == 0) {
        return strdup(elem);
    } else {
        char *tmp = fmtstr("%s %s", acc, elem);
        free(acc);
        return tmp;
    }
}

int alias_b(Shell *shell, vec_t *args)
{
    size_t count = lvec_size(args);
    if (count == 1)
        return disp_all_alias(shell);
    else if (count == 2)
        return disp_alias(shell, lvec_at(args, 1));
    else if (count >= 3)
        return add_alias(
            shell, lvec_at(args, 1), lvec_reduce(args, join_strings, 0, 0));
    return 1;
}
