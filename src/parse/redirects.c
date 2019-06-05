/*
** EPITECH PROJECT, 2019
** 42sh [WSL]
** File description:
** redirects
*/

#include "shell.h"

static const char *delim[] = {
    "<<",
    ">>",
    "<",
    ">",
    0,
};

static const RedirectType types[] = {
    REDIR_TYPE_DOUBLE_LEFT,
    REDIR_TYPE_DOUBLE_RIGHT,
    REDIR_TYPE_SIMPLE_LEFT,
    REDIR_TYPE_SIMPLE_RIGHT,
    0,
};

OPTION(Redirect) parse_redirect(const char *line)
{
    if (line == 0)
        return NONE(Redirect);

    size_t idx = 0;
    while (line[idx] >= '0' && line[idx] <= '9')
        idx += 1;

    ssize_t fd = (idx ? strtol(line, 0, 10) : -1);

    size_t type_idx = 0;
    while (
        // clang-format off
        delim[type_idx] &&
        lstr_starts_with(line + idx, delim[type_idx]) == false
        // clang-format on
    ) {
        type_idx += 1;
    }

    if (delim[type_idx] == 0)
        return NONE(Redirect);

    RedirectType type = types[type_idx];

    if (fd == -1) {
        switch (type) {
        case REDIR_TYPE_SIMPLE_LEFT:
        case REDIR_TYPE_DOUBLE_LEFT:
            fd = 0;
            break;
        case REDIR_TYPE_SIMPLE_RIGHT:
        case REDIR_TYPE_DOUBLE_RIGHT:
            fd = 1;
            break;
        }
    }

    idx += strlen(delim[type_idx]);

    RedirectKind kind = REDIR_KIND_FILE;
    if (line[idx] == '&') {
        kind = REDIR_KIND_FD;
        idx += 1;
    }

    if (line[idx] != 0)
        return NONE(Redirect);

    Redirect redirect = (Redirect){
        .type = type,
        .kind = kind,
        .from_fd = fd,
        .to_fd = 0,
    };

    return SOME(Redirect, redirect);
}

OPTION(SizeT) span_redirect(const char *line)
{
    if (line == 0)
        return NONE(SizeT);

    size_t idx = 0;
    while (line[idx] >= '0' && line[idx] <= '9')
        idx += 1;

    size_t type_idx = 0;
    while (
        // clang-format off
        delim[type_idx] &&
        lstr_starts_with(line + idx, delim[type_idx]) == false
        // clang-format on
    ) {
        type_idx += 1;
    }

    if (delim[type_idx] == 0)
        return NONE(SizeT);

    size_t len = strlen(delim[type_idx]);
    idx += (len + (line[idx + len] == '&'));

    return SOME(SizeT, idx);
}
