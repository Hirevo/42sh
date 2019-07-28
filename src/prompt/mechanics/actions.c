/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** actions
*/

#include "my.h"
#include "shell.h"
#include "autocompletion.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void action_cursor_left(Shell *shell, char **line)
{
    (void)(line);
    if (shell->w.cur) {
        shell->w.cur -= 1;
        writestr(shell->w.backw);
    }
}

void action_cursor_right(Shell *shell, char **line)
{
    if ((*line) && shell->w.cur < strlen(*line)) {
        shell->w.cur += 1;
        writestr(shell->w.forw);
    }
}

void action_cursor_backspace(Shell *shell, char **line)
{
    if (!(*line) || (*line)[0] == 0 || !shell->w.cur)
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

void action_cursor_delete(Shell *shell, char **line)
{
    if (!(*line) || (*line)[0] == 0 || shell->w.cur >= strlen(*line))
        return;
    delete_char(line, shell->w.cur + 1);
    if (shell->tty) {
        writestr((*line) + shell->w.cur);
        writestr(" ");
        shell->w.cur -= 1;
        pos_cursor(shell, *line);
        shell->w.cur += 1;
    }
}

void action_cursor_up(Shell *shell, char **line)
{
    suppress_line(shell, *line);
    if (shell->hist.cur == -1) {
        free(shell->hist.cur_line);
        if (*line)
            shell->hist.cur_line = strdup(*line);
        else
            shell->hist.cur_line = NULL;
        shell->hist.cur = shell->hist.arr->size - 1;
    } else if (shell->hist.cur > 0)
        shell->hist.cur -= 1;
    free(*line);
    *line = construct_alias(lvec_at(shell->hist.arr, shell->hist.cur));
    if (*line) {
        writestr(*line);
        shell->w.cur = strlen(*line);
    }
}

void action_cursor_down(Shell *shell, char **line)
{
    if (shell->hist.cur == -1)
        return;
    suppress_line(shell, *line);
    if ((size_t)(shell->hist.cur) == (shell->hist.arr->size - 1))
        return set_hist_line(shell, line);
    else
        shell->hist.cur += 1;
    free(*line);
    *line = construct_alias(shell->hist.arr->arr[shell->hist.cur]);
    writestr(*line);
    shell->w.cur = strlen(*line);
}

void action_cursor_home(Shell *shell, char **line)
{
    (void)(line);
    while (shell->w.cur > 0) {
        shell->w.cur -= 1;
        writestr(shell->w.backw);
    }
}

void action_cursor_end(Shell *shell, char **line)
{
    size_t len = ((*line) ? strlen(*line) : 0);

    while (shell->w.cur < len) {
        shell->w.cur += 1;
        writestr(shell->w.forw);
    }
}

void action_autocomplete(Shell *shell, char **line)
{
    autocomplete(shell, line);
}

void action_clear_term(Shell *shell, char **line)
{
    clear_term(shell, *line);
}

void action_open_editor(Shell *shell, char **line)
{
    prompt_open_editor(shell, line);
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

void parse_escape_sequence(Shell *shell, char **line, char init)
{
    RESULT(PromptAction) opt_action = buffer_seq(shell, init);
    if (IS_OK(opt_action)) {
        PromptAction action = RES_UNWRAP(opt_action);
        action(shell, line);
    } else {
        char *rest = RES_UNWRAP_ERR(opt_action);
        if (rest) {
            size_t len = strlen(rest);
            for (size_t idx = 0; idx < len; idx++) {
                if (isprint(rest[idx])) {
                    add_char(shell, line, rest[idx]);
                }
            }
            free(rest);
        }
    }
}

void clear_term(Shell *shell, char *line)
{
    if (shell->tty) {
        writestr(shell->w.clear);
        print_prompt(shell);
        if (line)
            writestr(line);
        pos_cursor(shell, line);
    }
}
