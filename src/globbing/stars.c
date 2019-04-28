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

static void update_glob(Shell *shell, char *arg, int *i, glob_t *list)
{
    sanitize_glob(list);
    char *file = construct_alias(list->gl_pathv);
    char *tmp = fmtstr(
        "%.*s%s%s", *i, shell->line, file, shell->line + *i + strlen(arg));
    free(shell->line);
    shell->line = tmp;
    *i += strlen(file);
    free(file);
    free(arg);
}

static void glob_stars(Shell *shell, char *arg, int *i)
{
    glob_t list;

    if (!arg)
        return;
    list.gl_offs = 1;
    if (glob(arg, GLOB_TILDE | GLOB_BRACE, NULL, &list) != 0) {
        *i += strlen(arg) - 1;
        free(arg);
        globfree(&list);
        return;
    }
    if (list.gl_pathc == 0) {
        *i += strlen(arg) - 1;
        free(arg);
        globfree(&list);
        return;
    }
    update_glob(shell, arg, i, &list);
    *i -= 1;
    globfree(&list);
}

int parse_stars(Shell *shell)
{
    int i = -1;
    int len;

    while (shell->line[++i]) {
        if (shell->line[i] == '\\')
            i += !!(shell->line[i + 1]);
        else if (shell->line[i] == '\'') {
            i += 1;
            while (shell->line[i] && shell->line[i] != '\'')
                i += 1;
            i -= (shell->line[i] == 0);
        } else if (shell->line[i] == '"')
            skip_string(shell->line, &i);
        else if (!is_space(shell->line[i])) {
            len = i;
            while (shell->line[len]) {
                if (shell->line[len] == '\\')
                    len += !!(shell->line[len + 1]);
                else if (is_space(shell->line[len]))
                    break;
                len += 1;
            }
            glob_stars(shell, strndup(shell->line + i, len - i), &i);
        }
    }
    return 0;
}
