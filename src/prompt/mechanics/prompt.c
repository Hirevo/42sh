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

void wait_input(void)
{
    struct pollfd events = (struct pollfd){
        .fd = 0,
        .events = POLLIN,
        .revents = 0,
    };

    poll(&events, 1, -1);
}

void color_text(Shell *shell, char *line)
{
    for (size_t i = 0; i < shell->w.cur; i++)
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
    if (shell->ioctl && shell->w.smkx)
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
        if (ch == '\n' || ch == 0x00 || ch == 0x04) {
            color_text(shell, line);
            break;
        }
        parse_escape_sequence(shell, &line, ch);
    }
    if (shell->tty && tcsetattr(0, TCSANOW, &shell->w.oterm) == -1) {
        handle_error("tcsetattr");
    }
    if (shell->ioctl && shell->w.rmkx) {
        writestr(shell->w.rmkx);
    }
    return SOME(CharPtr, line);
}
