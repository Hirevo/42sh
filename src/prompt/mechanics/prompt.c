/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "auto_complete.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void block_read_zero(void)
{
    fd_set rdfs;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    select(1, &rdfs, NULL, NULL, NULL);
}

static void make_action(shell_t *shell, char c)
{
    if (c == 12)
        clear_term(shell);
    else if (c == 24) {
        block_read_zero();
        c = get_input();
        if (c == 5)
            tmp_file(shell);
        else if (c != -1)
            insert_char(&shell->line, c);
    }
    else if (c == 127)
        remove_char(shell);
    else if (shell->tty && c == '\t')
        auto_complete(shell, getenv("PATH"));
    else if (shell->tty && (c == shell->w.forw[0] || c == shell->w.backw[0]))
        move_cursor(shell, c);
    else
        add_char(shell, c);
}

void color_text(shell_t *shell)
{
    while (shell->w.cur-- != 0)
        write(1, shell->w.backw, strlen(shell->w.backw));
    if (shell->line) {
        my_putstr("\033[1m\033[38;2;255;98;0m");
        my_putstr(shell->line);
        my_putstr("\033[0m");
    }
}

void prompt_line(shell_t *shell)
{
    char c = -1;

    if (shell->tty)
        set_raw(&shell->w.oterm);
    shell->hist.cur = -1;
    while (c != 10) {
        block_read_zero();
        c = get_input();
        if (c == -1) {
            if (shell->tty)
                continue;
            else
                return;
        }
        if (c == 10 && !shell->line)
            shell->line = strdup("");
        if (c == 10 || c == 0 || c == 4 || (c == -2 && !shell->tty)) {
            color_text(shell);
            break;
        }
        make_action(shell, c);
    }
    if (shell->tty && tcsetattr(0, TCSANOW, &shell->w.oterm) == -1)
        handle_error("tcsetattr");
}
