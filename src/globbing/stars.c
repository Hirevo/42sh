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
    char *tmp;
    char *file;

    sanitize_glob(list);
    file = construct_alias(list->gl_pathv);
    asprintf(&tmp, "%.*s%s%s", *i, shell->line, file,
        shell->line + *i + strlen(arg));
    free(shell->line);
    shell->line = tmp;
    *i += strlen(file);
    free(file);
    free(arg);
    free_tab(list->gl_pathv);
}

static void glob_stars(Shell *shell, char *arg, int *i)
{
    glob_t list;

    if (!arg)
        return;
    list.gl_offs = 1;
    glob(arg, GLOB_TILDE | GLOB_BRACE, NULL, &list);
    if (list.gl_pathc == 0) {
        *i += strlen(arg);
        free(arg);
    } else
        update_glob(shell, arg, i, &list);
    *i -= 1;
}

int parse_stars(Shell *shell)
{
    int i = -1;
    int len;

    while (shell->line[++i]) {
        if (shell->line[i] == '\\')
            i += !!(shell->line[i + 1]);
        else if (shell->line[i] == '\'' || shell->line[i] == '"')
            skip_string(shell->line, &i);
        else if (!is_space(shell->line[i])) {
            len = 0;
            while (shell->line[i + len] && !is_space(shell->line[i + len]))
                len += 1;
            glob_stars(shell, strndup(shell->line + i, len), &i);
        }
    }
    return 0;
}
