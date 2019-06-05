/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** actions
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void remove_char(Shell *shell, char **line)
{
    if (!(*line) || !strlen(*line) || !shell->w.cur)
        return;
    delete_char(line, shell->w.cur);
    if (shell->w.cur) {
        shell->w.cur -= 1;
    }
    if (shell->tty) {
        writestr(shell->w.backw);
        writestr((*line) + shell->w.cur);
        writestr(" ");
        shell->w.cur -= 1;
        pos_cursor(shell, *line);
        shell->w.cur += 1;
    }
}

void add_char(Shell *shell, char **line, char ch)
{
    insert_char_cur(line, ch, shell->w.cur);
    if (shell->tty) {
        writestr((*line) + shell->w.cur);
        shell->w.cur += 1;
        pos_cursor(shell, *line);
    } else {
        shell->w.cur += 1;
    }
}

void pos_cursor(Shell *shell, char *line)
{
    if (!line)
        return;
    int c = strlen(line) - shell->w.cur - 1;
    while (c-- >= 0) {
        writestr(shell->w.backw);
    }
}

void move_cursor(Shell *shell, char **line, char c)
{
    void (*cur_fct[6])(Shell *, char **);

    char *str;
    int dir;
    buffer_seq(shell, &str, &dir, c);
    if (dir == -1) {
        free(str);
        return;
    }
    get_cur_fcts(cur_fct);
    cur_fct[dir - 1](shell, line);
    free(str);
}

void clear_term(Shell *shell, char *line)
{
    if (shell->tty) {
        writestr(shell->w.clear);
        init_prompt(shell);
        if (line)
            writestr(line);
        pos_cursor(shell, line);
    }
}
