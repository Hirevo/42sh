/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** advanced
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_hist_line(Shell *shell, char **line)
{
    free(*line);
    if (shell->hist.cur_line) {
        *line = strdup(shell->hist.cur_line);
    } else {
        *line = NULL;
    }
    if (*line) {
        writestr(*line);
        shell->w.cur = strlen(*line);
    }
    shell->hist.cur = -1;
}

void suppress_line(Shell *shell, char *line)
{
    size_t len = ((line != NULL) ? strlen(line) : 0);

    while (shell->w.cur < len) {
        shell->w.cur += 1;
        writestr(shell->w.forw);
    }
    while (shell->w.cur > 0) {
        shell->w.cur -= 1;
        writestr(shell->w.backw);
        writestr(" ");
        writestr(shell->w.backw);
    }
}
