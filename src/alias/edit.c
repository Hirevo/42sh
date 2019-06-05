/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** edit
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

static bool equals_alias(void *ctx, void *elem, size_t idx)
{
    (void)(idx);
    return lstr_equals(ctx, elem);
}

OPTION(CharPtr) substitute_alias(Shell *shell, char *line, size_t idx)
{
    vec_t *substituted = lvec_new();
    size_t len = strcspn(line + idx, " \t><;|");
    char *considered = strndup(line + idx, len);
    char *matched = 0;

    while (1) {
        matched = lhmap_get(shell->aliases, considered);
        if (matched == 0)
            break;
        ssize_t found = lvec_find_index(substituted, equals_alias, considered);
        if (found > 0) {
            eputstr("error: command denied due to alias loop.\n");
            free(line);
            free(considered);
            lvec_clear(substituted, true);
            lvec_drop(substituted);
            return NONE(CharPtr);
        } else if (found == 0) {
            free(considered);
            lvec_clear(substituted, true);
            lvec_drop(substituted);
            return SOME(CharPtr, line);
        }
        lvec_push_front(substituted, 1, considered);
        char *replaced =
            fmtstr("%.*s%s%s", idx, line, matched, line + idx + len);
        free(line);
        line = replaced;
        len = strcspn(line + idx, " \t><;|");
        considered = strndup(line + idx, len);
    }
    free(considered);
    lvec_clear(substituted, true);
    lvec_drop(substituted);
    return SOME(CharPtr, line);
}

// TODO: Add awareness of backslashes
OPTION(CharPtr) substitute_aliases(Shell *shell, char *line)
{
    bool is_command = true;
    for (size_t idx = 0; line[idx]; idx++) {
        if (line[idx] == '\\') {
            idx += !!(line[idx + 1]);
        } else if (
            // clang-format off
            is_space(line[idx]) ||
            is_separator(line[idx])
            // clang-format on
        ) {
            while (
                // clang-format off
                is_space(line[idx]) ||
                is_separator(line[idx])
                // clang-format on
            ) {
                if (is_delimiter(line[idx++])) {
                    is_command = true;
                }
            }
            idx -= 1;
        } else if (is_command) {
            is_command = false;
            OPTION(CharPtr) opt = substitute_alias(shell, line, idx);
            if (IS_NONE(opt)) {
                return opt;
            } else {
                line = OPT_UNWRAP(opt);
                idx += strcspn(line + idx, " \t><;|");
            }
        } else {
            idx += (strcspn(line + idx, " \t><;|") - 1);
        }
    }
    return SOME(CharPtr, line);
}
