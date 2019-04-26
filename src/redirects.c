/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** redirects
*/

#include "my.h"
#include "shell.h"
#include "reports.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int setup_right_redirect(Command *head, int *fds, int i)
{
    int fd = open(
        head->r_name, O_WRONLY | O_CREAT | (i ? O_TRUNC : O_APPEND), 0644);

    (void)(fds);
    if (fd == -1) {
        if (errno == EISDIR) {
            return eputstr("%s: Is a directory.\n", head->r_name), -1;
        } else
            return -1;
    }
    dup2(fd, 1);
    return fd;
}

int setup_left_redirect(char *name, int type)
{
    int fd;
    int i[2];

    if (!type) {
        if (pipe(i) == -1)
            return -1;
        fd = i[0];
        if (isatty(0))
            my_putstr("> ");
        return buffer_input(name, i);
    } else if ((fd = open(name, O_RDONLY)) == -1)
        return -1;
    return fd;
}

int prepare_redirect(Command *head, char **type, char **name, size_t i)
{
    *type = lvec_remove(head->av, i);
    if (lvec_size(head->av) <= i) {
        return eputstr("missing name for redirect.\n"), -1;
    }
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
    Command *head;
    Command *last;

    last = NULL;
    head = shell->commands;
    while (head) {
        if (check_redirects(head, last) == -1)
            return -1;
        for (size_t i = 0; i < lvec_size(head->av); i++) {
            if (is_right_redirect(lvec_at(head->av, i))) {
                if (prepare_redirect(
                        head, &head->r_type, &head->r_name, i--) == -1)
                    return -1;
            } else if (is_left_redirect(lvec_at(head->av, i)))
                if (prepare_redirect(
                        head, &head->l_type, &head->l_name, i--) == -1)
                    return -1;
        }
        last = head;
        head = head->next;
    }
    return 0;
}
