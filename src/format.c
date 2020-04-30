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
    char *add_slash = ((lstr_ends_with(p1, "/") || lstr_equals(p1, "")) ? "" : "/");
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

char *fmt_seconds(time_t seconds)
{
#define YEAR 31536000
#define MONTH 2592000
#define WEEK 604800
#define DAY 86400
#define HOUR 3600
#define MINUTE 60

    char *str = NULL;

    if (seconds > YEAR) {
        long years = seconds / YEAR;
        seconds -= years * YEAR;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, years, (years - 1) ? "years" : "year");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", years, (years - 1) ? "years" : "year");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds > MONTH) {
        long months = seconds / MONTH;
        seconds -= months * MONTH;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, months, (months - 1) ? "months" : "month");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", months, (months - 1) ? "months" : "month");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds > WEEK) {
        long weeks = seconds / WEEK;
        seconds -= weeks * WEEK;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, weeks, (weeks - 1) ? "weeks" : "week");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", weeks, (weeks - 1) ? "weeks" : "week");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds > DAY) {
        long days = seconds / DAY;
        seconds -= days * DAY;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, days, (days - 1) ? "days" : "day");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", days, (days - 1) ? "days" : "day");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds > HOUR) {
        long hours = seconds / HOUR;
        seconds -= hours * HOUR;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, hours, (hours - 1) ? "hrs" : "hr");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", hours, (hours - 1) ? "hrs" : "hr");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds > MINUTE) {
        long minutes = seconds / MINUTE;
        seconds -= minutes * MINUTE;
        if (str) {
            char *tmp = fmtstr("%s %ld %s", str, minutes, (minutes - 1) ? "mins" : "min");
            if (!tmp) {
                return NULL;
            }
            free(str);
            str = tmp;
        } else {
            str = fmtstr("%ld %s", minutes, (minutes - 1) ? "mins" : "min");
            if (!str) {
                return NULL;
            }
        }
    }

    if (seconds && str) {
        char *tmp = fmtstr("%s %ld %s", str, seconds, (seconds - 1) ? "secs" : "sec");
        if (!tmp) {
            return NULL;
        }
        free(str);
        str = tmp;
    } else if (!str) {
        str = fmtstr("%ld %s", seconds, (seconds - 1) ? "secs" : "sec");
        if (!str) {
            return NULL;
        }
    }

    return str;
}
