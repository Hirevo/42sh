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

void move_end(shell_t *shell)
{
    int len;

    len = strlen(shell->line);
    while (shell->w.cur < len) {
        write(1, shell->w.forw, strlen(shell->w.forw));
        shell->w.cur += 1;
    }
}

void move_home(shell_t *shell)
{
    while (shell->w.cur > 0) {
        write(1, shell->w.backw, strlen(shell->w.backw));
        shell->w.cur -= 1;
    }
}

void set_hist_line(shell_t *shell)
{
    free(shell->line);
    if (shell->hist.cur_line)
        shell->line = strdup(shell->hist.cur_line);
    else
        shell->line = NULL;
    if (shell->line) {
        my_putstr(shell->line);
        shell->w.cur = strlen(shell->line);
    }
    shell->hist.cur = -1;
}

void suppress_line(shell_t *shell)
{
    int len;

    len = ((shell->line != NULL) ? strlen(shell->line) : 0);
    while (shell->w.cur < len) {
        shell->w.cur += 1;
        write(1, shell->w.forw, strlen(shell->w.forw));
    }
    while (shell->w.cur > 0) {
        shell->w.cur -= 1;
        write(1, shell->w.backw, strlen(shell->w.backw));
        write(1, " ", 1);
        write(1, shell->w.backw, strlen(shell->w.backw));
    }
}
