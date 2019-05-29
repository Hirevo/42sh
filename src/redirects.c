/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** redirects
*/

#include "get_next_line.h"
#include "my.h"
#include "reports.h"
#include "shell.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

OPTION(Int) setup_right_redirect(Command *head, bool single)
{
    const int flag = single ? O_TRUNC : O_APPEND;
    int fd = open(head->r_name, O_WRONLY | O_CREAT | flag, 0644);

    if (fd == -1) {
        if (errno == EISDIR) {
            return eputstr("%s: Is a directory.\n", head->r_name), NONE(Int);
        } else {
            return NONE(Int);
        }
    }
    fflush(stdout);
    dup2(fd, 1);
    return SOME(Int, fd);
}

OPTION(Int) setup_left_redirect(Command *head, bool single)
{
    if (single == false) {
        int fds[2];
        if (pipe(fds) == -1)
            return NONE(Int);
        if (isatty(0))
            writestr("> ");
        for (char *str = get_next_line(0); str; str = get_next_line(0)) {
            if (str && strcmp(str, head->l_name) == 0) {
                free(str);
                break;
            } else {
                dwritestr(fds[1], str);
                dwritechar(fds[1], '\n');
                free(str);
                if (isatty(0))
                    writestr("> ");
            }
        }
        close(fds[1]);
        dup2(fds[0], 0);
        return SOME(Int, fds[0]);
    } else {
        int fd = open(head->l_name, O_RDONLY);
        if (fd == -1)
            return NONE(Int);
        dup2(fd, 0);
        return SOME(Int, fd);
    }
}

int prepare_redirect(Command *head, char **type, char **name, size_t i)
{
    free(*type);
    *type = lvec_remove(head->av, i);
    if (lvec_size(head->av) <= i) {
        return eputstr("missing name for redirect.\n"), -1;
    }
    free(*name);
    *name = lvec_remove(head->av, i);
    if (lvec_size(head->av) == 0)
        return eputstr("invalid null command.\n"), -1;
    return 0;
}

int check_redirects(Command *head, Command *last)
{
    int i;
    int r;
    int l;

    init_redirect(head, &r, &l, &i);
    for (size_t i = 0; i < lvec_size(head->av); i++)
        if (is_right_redirect(lvec_at(head->av, i)) ||
            is_left_redirect(lvec_at(head->av, i))) {
            if (lvec_size(head->av) <= i + 1)
                return eputstr("missing name for redirect.\n"), -1;
            else
                (is_left_redirect(lvec_at(head->av, i))) ? (l += 1) : (r += 1);
        }
    if (r > 1 || (r == 1 && head->link == '|'))
        return eputstr("ambiguous output redirect.\n"), -1;
    else if (l > 1 || (l == 1 && last && last->link == '|'))
        return eputstr("ambiguous input redirect.\n"), -1;
    return 0;
}

int set_redirects(Shell *shell)
{
    Command *head = shell->commands;
    Command *last = NULL;

    while (head) {
        if (check_redirects(head, last) == -1)
            return -1;
        for (size_t i = 0; i < lvec_size(head->av); i++) {
            if (is_right_redirect(lvec_at(head->av, i))) {
                if (prepare_redirect(
                        head, &head->r_type, &head->r_name, i--) == -1) {
                    return -1;
                }
            } else if (is_left_redirect(lvec_at(head->av, i))) {
                if (prepare_redirect(
                        head, &head->l_type, &head->l_name, i--) == -1) {
                    return -1;
                }
            }
        }
        last = head;
        head = head->next;
    }
    return 0;
}
