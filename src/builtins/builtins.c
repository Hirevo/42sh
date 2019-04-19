/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** builtins
*/

#include "shell.h"

static void *render_key(void *ctx, void *acc, void *elem, size_t idx)
{
    (void)(ctx);
    if (idx == 0) {
        return strdup(elem);
    } else {
        acc = lstr_append(acc, "\\\\n");
        return lstr_append(acc, sanitize_double_quotes(elem, false));
    }
}

int builtins_b(shell_t *shell, vec_t *args)
{
    (void)(args);
    vec_t *keys = lhmap_keys(shell->builtins);

    if (shell->tty) {
        char *rendered_keys = lvec_reduce(keys, render_key, 0, 0);

        char *rendered = 0;
        static const char *command = "echo \"%s\" | sort | column";
        if (asprintf(&rendered, command, rendered_keys) == -1) {
            free(rendered_keys);
            return 1;
        }
        free(rendered_keys);

        quick_exec(shell, rendered);
    } else {
        for (size_t i = 0; i < lvec_size(keys); i++)
            putstr("%s\n", lvec_at(keys, i));
    }
    return 0;
}