/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cursor
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool match_sequence(void *ctx, void *elem, size_t idx)
{
    (void)(idx);
    return lstr_equals(ctx, elem);
}

static bool prefix_sequence(void *ctx, void *elem, size_t idx)
{
    (void)(idx);
    return lstr_starts_with(elem, ctx);
}

RESULT(PromptAction) buffer_seq(Shell *shell, char init)
{
    char *buffer = strdup("");
    if (buffer == 0)
        return ERR(PromptAction, 0);

    vec_t *sequences = lvec_clone(lhmap_keys(shell->w.actions));
    if (sequences == 0) {
        free(buffer);
        return ERR(PromptAction, 0);
    }

    char ch = init;
    do {
        if (ch == -1) {
            wait_input();
            ch = get_input();
        }
        insert_char_cur(&buffer, ch, strlen(buffer));
        char *found = lvec_find(sequences, match_sequence, buffer);
        if (found) {
            lvec_drop(sequences);
            free(buffer);
            OPTION(PromptAction)
            opt = OPT_FROM_NULLABLE(
                PromptAction, lhmap_get(shell->w.actions, found));
            if (IS_SOME(opt)) {
                return OK(PromptAction, OPT_UNWRAP(opt));
            } else {
                //? Should effectively be unreachable.
                return ERR(PromptAction, 0);
            }
        }
        lvec_filter(sequences, prefix_sequence, buffer);
        ch = -1;
    } while (lvec_size(sequences) > 0);

    lvec_drop(sequences);
    return ERR(PromptAction, buffer);
}
