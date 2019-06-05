/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** history
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static OPTION(CharPtr)
    insert_one_hist(Shell *shell, char *line, size_t idx, size_t n)
{
    char **last = lvec_back(shell->hist.arr);
    if (last == 0)
        return NONE(CharPtr);

    size_t len = 0;
    while (last && last[len])
        len += 1;
    if (n >= len) {
        eputstr("bad ! arg selector.\n");
        return NONE(CharPtr);
    }

    char *str = fmtstr("%.*s%s%s", (int)(idx), line, last[n], line + idx + 3);
    if (str == NULL)
        return NONE(CharPtr);
    free(line);

    return SOME(CharPtr, str);
}

static OPTION(CharPtr) insert_full_hist(Shell *shell, char *line, size_t i)
{
    char **last = lvec_back(shell->hist.arr);
    if (last == 0)
        return NONE(CharPtr);

    size_t len = 0;
    size_t idx = 0;
    for (idx = 0; last[idx]; idx++)
        len += strlen(last[idx]);
    len += strlen(line) - 2 + idx;

    char *str = calloc(len + 1, sizeof(char));
    if (str == NULL)
        return NONE(CharPtr);

    strncpy(str, line, i);
    for (idx = 0; last[idx]; idx++)
        strcat(idx ? strcat(str, " ") : str, last[idx]);
    strcat(str, line + i + 2);
    free(line);

    return SOME(CharPtr, str);
}

static OPTION(CharPtr) insert_last_hist(Shell *shell, char *line, size_t i)
{
    char **last = lvec_back(shell->hist.arr);
    if (last == 0)
        return NONE(CharPtr);

    size_t idx = 0;
    while (last[idx])
        idx += 1;
    idx -= 1;

    char *str = fmtstr("%.*s%s%s", (int)(i), line, last[idx], line + i + 2);
    free(line);

    return SOME(CharPtr, str);
}

OPTION(CharPtr) substitute_history(Shell *shell, char *line, bool to_save)
{
    int i = -1;
    char *last = line;

    while (lvec_back(shell->hist.arr) && line[++i]) {
        if (line[i] == '\\') {
            i += !!(line[i + 1]);
        } else if (line[i] == '\'') {
            i += 1;
            while (line[i] && line[i] != '\'')
                i += 1;
            i -= (line[i] == 0);
        } else if (lstr_starts_with(line + i, "!!")) {
            OPTION(CharPtr) opt = insert_full_hist(shell, line, i);
            if (IS_NONE(opt)) {
                return opt;
            } else {
                line = OPT_UNWRAP(opt);
            }
        } else if (lstr_starts_with(line + i, "!$")) {
            OPTION(CharPtr) opt = insert_last_hist(shell, line, i);
            if (IS_NONE(opt)) {
                return opt;
            } else {
                line = OPT_UNWRAP(opt);
            }
        } else if (lstr_starts_with(line + i, "!:") &&
            (line[i + 2] >= '0' && line[i + 2] <= '9')) {
            OPTION(CharPtr)
            opt = insert_one_hist(shell, line, i, (size_t)(line[i + 2] - '0'));
            if (IS_NONE(opt)) {
                return opt;
            } else {
                line = OPT_UNWRAP(opt);
            }
        }
    }

    char **back = lvec_back(shell->hist.arr);
    char *str = NULL;
    if (back != NULL) {
        str = construct_alias(back);
    }
    if (last != line)
        putstr("%s\n", line);
    if (to_save && lstr_equals(line, "exit") == false &&
        (back == NULL || lstr_equals(str, line) == false))
        add_hist_elem(shell, line);
    free(str);

    return SOME(CharPtr, line);
}
