/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "auto_complete.h"
#include "my.h"
#include "shell.h"
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void wait_input(void)
{
    struct pollfd events = (struct pollfd){
        .fd = 0,
        .events = POLLIN,
        .revents = 0,
    };

    poll(&events, 1, -1);
}

static void make_action(shell_t *shell, char c)
{
    if (c == 12)
        clear_term(shell);
    else if (c == 24) {
        wait_input();
        c = get_input();
        if (c == 5)
            tmp_file(shell);
        else if (c != -1)
            insert_char(&shell->line, c);
    } else if (c == 127)
        remove_char(shell);
    else if (shell->tty && c == '\t')
        auto_complete(shell, getenv("PATH"));
    else if (shell->tty && c == '\e')
        move_cursor(shell, c);
    else
        add_char(shell, c);
}

void color_text(shell_t *shell)
{
    while (shell->w.cur-- != 0)
        my_putstr(shell->w.backw);
    if (shell->line) {
        my_putstr("\e[1m\e[38;2;255;98;0m");
        my_putstr(shell->line);
        my_putstr("\e[0m");
    }
}

void prompt_line(shell_t *shell)
{
    char c = -1;

    if (shell->tty)
        set_raw(&shell->w.oterm);
    if (shell->ioctl)
        my_putstr(shell->w.smkx);
    shell->hist.cur = -1;
    while (c != '\n') {
        wait_input();
        c = get_input();
        if (c == -1) {
            if (shell->tty)
                continue;
            else {
                if (shell->ioctl)
                    my_putstr(shell->w.rmkx);
                return;
            }
        }
        if (c == '\n' && !shell->line)
            shell->line = strdup("");
        if (c == '\n' || c == 0 || c == 4 || (c == -2 && !shell->tty)) {
            color_text(shell);
            break;
        }
        make_action(shell, c);
    }
    if (shell->tty && tcsetattr(0, TCSANOW, &shell->w.oterm) == -1)
        handle_error("tcsetattr");
    if (shell->ioctl)
        my_putstr(shell->w.rmkx);
}
