/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** loop
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int can_replace(Shell *shell, char *line)
{
    int i;
    char **ret;

    i = -1;
    while (shell->subst.list && shell->subst.list[++i])
        if (lstr_equals(shell->subst.list[i], line))
            return 0;
    i = (shell->subst.list == NULL) - 1;
    if (i == -1)
        while (shell->subst.list[++i])
            ;
    ret = calloc(i + 2, sizeof(char **));
    if (ret == NULL)
        handle_error("calloc");
    i = (shell->subst.list == NULL) - 1;
    if (i == -1)
        while (shell->subst.list[++i])
            ret[i] = shell->subst.list[i];
    ret[i++] = strdup(line);
    ret[i] = NULL;
    free(shell->subst.list);
    shell->subst.list = ret;
    return 1;
}

void free_subst(Shell *shell)
{
    int i;

    i = -1;
    while (shell->subst.list && shell->subst.list[++i])
        free(shell->subst.list[i]);
    free(shell->subst.list);
}

int detect_loop(Shell *shell, char *line, int i)
{
    if (!can_replace(shell, line) && i == shell->subst.idx) {
        dprintf(2, "Error: Command denied due to alias loop\n");
        return -1;
    }
    return 0;
}
