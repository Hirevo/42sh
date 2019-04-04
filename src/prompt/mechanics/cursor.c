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

void buffer_seq(shell_t *shell, char **str, int *dir, char c)
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

void move_forw(shell_t *shell)
{
    if (shell->line && shell->w.cur < ((int)strlen(shell->line))) {
        shell->w.cur += 1;
        my_putstr(shell->w.forw);
    }
}

void move_backw(shell_t *shell)
{
    if (shell->w.cur) {
        shell->w.cur -= 1;
        my_putstr(shell->w.backw);
    }
}

void move_upw(shell_t *shell)
{
    suppress_line(shell);
    if (shell->hist.cur == -1) {
        free(shell->hist.cur_line);
        if (shell->line)
            shell->hist.cur_line = strdup(shell->line);
        else
            shell->hist.cur_line = NULL;
        shell->hist.cur = shell->hist.arr->size - 1;
    } else if (shell->hist.cur > 0)
        shell->hist.cur -= 1;
    free(shell->line);
    shell->line = construct_alias(shell->hist.arr->arr[shell->hist.cur]);
    if (shell->line) {
        my_putstr(shell->line);
        shell->w.cur = strlen(shell->line);
    }
}

void move_downw(shell_t *shell)
{
    if (shell->hist.cur == -1)
        return;
    suppress_line(shell);
    if ((size_t)(shell->hist.cur) == (shell->hist.arr->size - 1))
        return set_hist_line(shell);
    else
        shell->hist.cur += 1;
    free(shell->line);
    shell->line = construct_alias(shell->hist.arr->arr[shell->hist.cur]);
    my_putstr(shell->line);
    shell->w.cur = strlen(shell->line);
}
