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

void buffer_seq(Shell *shell, char **str, int *dir, char c)
{
    *str = NULL;
    *dir = -1;
    insert_char_cur(str, c, 0);
    if (!shell->w.left || !shell->w.right || !shell->w.upw ||
        !shell->w.downw || !shell->w.home || !shell->w.end)
        return;
    while (*dir == -1 &&
        (strstr(shell->w.left, *str) || strstr(shell->w.right, *str) ||
            strstr(shell->w.upw, *str) || strstr(shell->w.downw, *str) ||
            strstr(shell->w.home, *str) || strstr(shell->w.end, *str))) {
        while (!(c = get_input()))
            ;
        insert_char_cur(str, c, strlen(*str));
        if (!strcmp(*str, shell->w.left))
            *dir = 1;
        else if (!strcmp(*str, shell->w.right))
            *dir = 2;
        else if (!strcmp(*str, shell->w.upw))
            *dir = 3;
        else if (!strcmp(*str, shell->w.downw))
            *dir = 4;
        else if (!strcmp(*str, shell->w.home))
            *dir = 5;
        else if (!strcmp(*str, shell->w.end))
            *dir = 6;
    }
}

void move_forw(Shell *shell, char **line)
{
    if (line && shell->w.cur < ((int)(strlen(*line)))) {
        shell->w.cur += 1;
        writestr(shell->w.forw);
    }
}

void move_backw(Shell *shell, char **line)
{
    (void)(line);
    if (shell->w.cur) {
        shell->w.cur -= 1;
        writestr(shell->w.backw);
    }
}

void move_upw(Shell *shell, char **line)
{
    suppress_line(shell, *line);
    if (shell->hist.cur == -1) {
        free(shell->hist.cur_line);
        if (*line) {
            shell->hist.cur_line = strdup(*line);
        } else {
            shell->hist.cur_line = NULL;
        }
        shell->hist.cur = shell->hist.arr->size - 1;
    } else if (shell->hist.cur > 0)
        shell->hist.cur -= 1;
    free(*line);
    *line = construct_alias(shell->hist.arr->arr[shell->hist.cur]);
    if (*line) {
        writestr(*line);
        shell->w.cur = strlen(*line);
    }
}

void move_downw(Shell *shell, char **line)
{
    if (shell->hist.cur == -1)
        return;
    suppress_line(shell, *line);
    if ((size_t)(shell->hist.cur) == (shell->hist.arr->size - 1)) {
        return set_hist_line(shell, line);
    } else {
        shell->hist.cur += 1;
    }
    free(*line);
    *line = construct_alias(shell->hist.arr->arr[shell->hist.cur]);
    writestr(*line);
    shell->w.cur = strlen(*line);
}
