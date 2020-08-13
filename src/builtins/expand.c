/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** expand
*/

#include "shell.h"

static void *join_strings(void *ctx, void *acc, void *elem, size_t idx)
{
    (void)(ctx);
    if (idx == 0) {
        return 0;
    } else if (acc == 0) {
        return strdup(elem);
    } else {
        char *tmp = fmtstr("%s %s", acc, elem);
        free(acc);
        return tmp;
    }
}

int expand_b(Shell *shell, vec_t *args)
{
    switch (lvec_size(args)) {
    case 0:
    case 1:
        eputstr("expand: too few arguments.\n");
        return 1;
    default: {
        char *command = lvec_reduce(args, join_strings, 0, 0);
        OPTION(CharPtr) opt_expanded = substitute_aliases(shell, command);
        if (IS_SOME(opt_expanded)) {
            char *expanded = OPT_UNWRAP(opt_expanded);
            printf("%s\n", expanded);
            return 0;
        } else {
            return 1;
        }
    }
    }
}
