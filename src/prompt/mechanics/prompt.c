/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "autocompletion.h"
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

static void make_action(Shell *shell, char **line, char ch)
{
    if (ch == 12) {
        clear_term(shell, *line);
    } else if (ch == 24) {
        wait_input();
        ch = get_input();
        if (ch == 5) {
            tmp_file(shell, line);
        } else if (ch != -1) {
            insert_char(line, ch);
        }
    } else if (ch == 127) {
        remove_char(shell, line);
    } else if (shell->tty && ch == '\t') {
        autocomplete(shell, line);
    } else if (shell->tty && ch == '\e') {
        move_cursor(shell, line, ch);
    } else {
        add_char(shell, line, ch);
    }
}

void color_text(Shell *shell, char *line)
{
    for (int i = 0; i < shell->w.cur; i++)
        writestr(shell->w.backw);
    if (line) {
        writestr("\e[1m\e[38;2;255;98;0m");
        writestr(line);
        writestr("\e[0m");
    }
}

OPTION(CharPtr) prompt_line(Shell *shell)
{
    if (shell->tty)
        set_raw(&shell->w.oterm);
    if (shell->ioctl)
        writestr(shell->w.smkx);
    shell->hist.cur = -1;
    char *line = 0;
    char ch = -1;
    while (ch != '\n') {
        wait_input();
        ch = get_input();
        if (ch == -1) {
            if (shell->tty) {
                continue;
            } else {
                if (shell->ioctl) {
                    writestr(shell->w.rmkx);
                }
                return SOME(CharPtr, line);
            }
        }
        if (ch == '\n' && !line) {
            line = strdup("");
        }
        if (ch == '\n' || ch == 0 || ch == 4 || (ch == -2 && !shell->tty)) {
            color_text(shell, line);
            break;
        }
        make_action(shell, &line, ch);
    }
    if (shell->tty && tcsetattr(0, TCSANOW, &shell->w.oterm) == -1) {
        handle_error("tcsetattr");
    }
    if (shell->ioctl) {
        writestr(shell->w.rmkx);
    }
    return SOME(CharPtr, line);
}
