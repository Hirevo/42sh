/*
** EPITECH PROJECT, 2019
** 42sh [WSL]
** File description:
** redirects
*/

#include <errno.h>
#include <fcntl.h>

#include "get_next_line.h"
#include "shell.h"

bool redirect_simple_left(Redirect *redirect)
{
    switch (redirect->kind) {
    case REDIR_KIND_FD:
        dup2(redirect->to_fd, redirect->from_fd);
        break;
    case REDIR_KIND_FILE: {
        int fd = open(redirect->to_name, O_RDONLY);
        if (fd == -1) {
            if (errno == EISDIR)
                eputstr("%s: Is a directory.\n", redirect->to_name);
            return false;
        }
        dup2(fd, redirect->from_fd);
        close(fd);
        break;
    }
    }
    return true;
}

bool redirect_simple_right(Redirect *redirect)
{
    switch (redirect->kind) {
    case REDIR_KIND_FD:
        dup2(redirect->to_fd, redirect->from_fd);
        break;
    case REDIR_KIND_FILE: {
        int fd = open(redirect->to_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            if (errno == EISDIR)
                eputstr("%s: Is a directory.\n", redirect->to_name);
            return false;
        }
        dup2(fd, redirect->from_fd);
        close(fd);
        break;
    }
    }
    return true;
}

bool redirect_double_left(Redirect *redirect)
{
    switch (redirect->kind) {
    case REDIR_KIND_FD:
        return eputstr("invalid redirection kind.\n"), false;
    case REDIR_KIND_FILE: {
        int fds[2];
        if (pipe(fds) == -1)
            return false;
        if (isatty(0))
            writestr("> ");
        for (char *str = get_next_line(0); str; str = get_next_line(0)) {
            if (str && lstr_equals(str, redirect->to_name)) {
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
        dup2(fds[0], redirect->from_fd);
        close(fds[0]);
        break;
    }
    }
    return true;
}

bool redirect_double_right(Redirect *redirect)
{
    switch (redirect->kind) {
    case REDIR_KIND_FD:
        dup2(redirect->to_fd, redirect->from_fd);
        break;
    case REDIR_KIND_FILE: {
        int fd = open(redirect->to_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            if (errno == EISDIR)
                eputstr("%s: Is a directory.\n", redirect->to_name);
            return false;
        }
        dup2(fd, redirect->from_fd);
        close(fd);
        break;
    }
    }
    return true;
}
