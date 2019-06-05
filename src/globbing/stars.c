/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** stars
*/

#include "my.h"
#include "shell.h"
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>

static void sanitize_glob(glob_t *list)
{
    for (size_t i = 0; list->gl_pathv[i]; i++)
        list->gl_pathv[i] = sanitize_single_arg(list->gl_pathv[i], 1);
}

OPTION(CharPtr) substitute_globs(Shell *shell, char *line)
{
    for (size_t idx = 0; line[idx]; idx++) {
        if (line[idx] == '\\') {
            idx += !!(line[idx + 1]);
        } else if (line[idx] == '\'') {
            idx += 1;
            while (line[idx] && line[idx] != '\'')
                idx += 1;
            idx -= (line[idx] == 0);
        } else if (line[idx] == '"') {
            skip_string(line, &idx);
        } else if (!is_space(line[idx])) {
            size_t len = idx;
            while (line[len]) {
                if (line[len] == '\\') {
                    len += !!(line[len + 1]);
                } else if (is_space(line[len])) {
                    break;
                }
                len += 1;
            }
            char *fragment = strndup(line + idx, len - idx);
            if (!fragment)
                return NONE(CharPtr);
            glob_t list;
            list.gl_offs = 1;
            if (glob(fragment, GLOB_TILDE | GLOB_BRACE, NULL, &list) != 0) {
                idx += strlen(fragment) - 1;
                free(fragment);
                globfree(&list);
                continue;
            }
            if (list.gl_pathc == 0) {
                idx += strlen(fragment) - 1;
                free(fragment);
                globfree(&list);
                continue;
            }
            sanitize_glob(&list);
            char *file = construct_alias(list.gl_pathv);
            char *tmp = fmtstr(
                "%.*s%s%s", idx, line, file, line + idx + strlen(fragment));
            free(line);
            line = tmp;
            idx += strlen(file);
            free(file);
            free(fragment);
            idx -= 1;
            globfree(&list);
        }
    }
    return SOME(CharPtr, line);
}
