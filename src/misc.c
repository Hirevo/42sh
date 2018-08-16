/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** misc
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

int is_valid_path(char *path)
{
    int i = 0;

    if (path[i] == '=')
        return 0;
    while (path[i] != '=')
        if (path[i++] == 0)
            return 0;
    return 1;
}

unsigned int get_unsigned_int(char *final)
{
    int i = strlen(final) - 1;
    unsigned int factor = 1;
    unsigned int result = 0;

    while (i >= 0) {
        if (final[i] == '-')
            result = 256 - result;
        else {
            result += (final[i] - '0') * factor;
            factor *= 10;
        }
        i -= 1;
    }
    return result;
}

int is_line_empty(char *line)
{
    int i = -1;

    while (line[++i] != 0)
        if (line[i] != ' ' && line[i] != '\t')
            return 0;
    free(line);
    return 1;
}

int is_char_alpha(char *c)
{
    int i = -1;

    while (c[++i]) {
        if ((c[i] < '0' || c[i] > '9') && (c[i] < 'a' || c[i] > 'z') &&
            (c[i] < 'A' || c[i] > 'Z') && c[i] != '_')
            return 0;
    }
    return 1;
}

int my_strlen_spe(char *path, char stop)
{
    int i = 0;

    while (path[i] != stop && path[i] != 0)
        i += 1;
    return i;
}
