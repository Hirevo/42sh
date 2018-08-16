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

void remove_char(shell_t *shell)
{
    if (!shell->line || !strlen(shell->line) || !shell->w.cur)
        return;
    delete_char(&shell->line, shell->w.cur);
    if (shell->w.cur)
        shell->w.cur -= 1;
    if (shell->tty) {
        write(1, shell->w.backw, strlen(shell->w.backw));
        write(
            1, shell->line + shell->w.cur, strlen(shell->line + shell->w.cur));
        write(1, " ", 1);
        shell->w.cur -= 1;
        pos_cursor(shell);
        shell->w.cur += 1;
    }
}

void add_char(shell_t *shell, char c)
{
    insert_char_cur(&shell->line, c, shell->w.cur);
    if (shell->tty) {
        write(
            1, shell->line + shell->w.cur, strlen(shell->line + shell->w.cur));
        shell->w.cur += 1;
        pos_cursor(shell);
    }
    else
        shell->w.cur += 1;
}

void pos_cursor(shell_t *shell)
{
    int c;

    if (!shell->line)
        return;
    c = strlen(shell->line) - shell->w.cur - 1;
    while (c-- >= 0)
        write(1, shell->w.backw, strlen(shell->w.backw));
}

void move_cursor(shell_t *shell, char c)
{
    char *str;
    int dir;
    void (*cur_fct[6])(shell_t *);

    buffer_seq(shell, &str, &dir, c);
    if (dir == -1) {
        free(str);
        return;
    }
    get_cur_fcts(cur_fct);
    cur_fct[dir - 1](shell);
    free(str);
}

void clear_term(shell_t *shell)
{
    if (shell->tty) {
        write(1, shell->w.clear, strlen(shell->w.clear));
        init_prompt(shell);
        if (shell->line)
            my_putstr(shell->line);
        pos_cursor(shell);
    }
}
