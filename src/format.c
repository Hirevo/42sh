/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** format
*/

#include "shell.h"

void putstr(const char *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    vprintf(fmt, list);
    va_end(list);
}

void eputstr(const char *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    vdprintf(2, fmt, list);
    va_end(list);
}

void dputstr(const int fd, const char *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    vdprintf(fd, fmt, list);
    va_end(list);
}

char *path_join(const char *p1, const char *p2)
{
    char *path = 0;
    char *add_slash = (lstr_ends_with(p1, "/") ? "" : "/");

    if (asprintf(&path, "%s%s%s", p1, add_slash, p2) == -1)
        return 0;
    return path;
}

char *pretty_path(const char *path)
{
    char *home = getenv("HOME");

    if (home == 0)
        return strdup(path);
    else if (lstr_equals(path, home)) {
        return strdup("~");
    } else if (lstr_starts_with(path, home)) {
        char *ret = 0;
        const char *npath = path + strlen(home) + !lstr_ends_with(home, "/");
        if (asprintf(&ret, "~/%s", npath) == -1)
            return 0;
        return ret;
    } else {
        return strdup(path);
    }
}
