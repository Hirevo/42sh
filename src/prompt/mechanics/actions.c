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

void remove_char(Shell *shell)
{
    if (!shell->line || !strlen(shell->line) || !shell->w.cur)
        return;
    delete_char(&shell->line, shell->w.cur);
    if (shell->w.cur)
        shell->w.cur -= 1;
    if (shell->tty) {
        writestr(shell->w.backw);
        writestr(shell->line + shell->w.cur);
        writestr(" ");
        shell->w.cur -= 1;
        pos_cursor(shell);
        shell->w.cur += 1;
    }
}

void add_char(Shell *shell, char c)
{
    insert_char_cur(&shell->line, c, shell->w.cur);
    if (shell->tty) {
        writestr(shell->line + shell->w.cur);
        shell->w.cur += 1;
        pos_cursor(shell);
    } else
        shell->w.cur += 1;
}

void pos_cursor(Shell *shell)
{
    int c;

    if (!shell->line)
        return;
    c = strlen(shell->line) - shell->w.cur - 1;
    while (c-- >= 0)
        writestr(shell->w.backw);
}

void move_cursor(Shell *shell, char c)
{
    char *str;
    int dir;
    void (*cur_fct[6])(Shell *);

    buffer_seq(shell, &str, &dir, c);
    if (dir == -1) {
        free(str);
        return;
    }
    get_cur_fcts(cur_fct);
    cur_fct[dir - 1](shell);
    free(str);
}

void clear_term(Shell *shell)
{
    if (shell->tty) {
        writestr(shell->w.clear);
        init_prompt(shell);
        if (shell->line)
            writestr(shell->line);
        pos_cursor(shell);
    }
}
