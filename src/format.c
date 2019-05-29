/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** format
*/

#include "shell.h"

void writechar(const char chr)
{
    write(1, &chr, 1);
}

void ewritechar(const char chr)
{
    write(2, &chr, 1);
}

void dwritechar(const int fd, const char chr)
{
    write(fd, &chr, 1);
}

void writestr(const char *str)
{
    write(1, str, strlen(str));
}

void ewritestr(const char *str)
{
    write(2, str, strlen(str));
}

void dwritestr(const int fd, const char *str)
{
    write(fd, str, strlen(str));
}

void putstr(const char *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    vdprintf(1, fmt, list);
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

char *fmtstr(const char *fmt, ...)
{
    va_list list;
    char *ret = 0;

    va_start(list, fmt);
    vasprintf(&ret, fmt, list);
    va_end(list);
    return ret;
}

char *path_join(const char *p1, const char *p2)
{
    char *add_slash =
        ((lstr_ends_with(p1, "/") || lstr_equals(p1, "")) ? "" : "/");

    return fmtstr("%s%s%s", p1, add_slash, p2);
}

char *pretty_path(const char *path)
{
    char *home = getenv("HOME");

    if (home == 0)
        return strdup(path);
    else if (lstr_equals(path, home)) {
        return strdup("~");
    } else if (lstr_starts_with(path, home)) {
        const char *npath = path + strlen(home) + !lstr_ends_with(home, "/");
        return fmtstr("~/%s", npath);
    } else {
        return strdup(path);
    }
}
