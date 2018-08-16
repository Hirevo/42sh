/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** buffer
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

int buffer_input(char *name, int i[2])
{
    char *str;
    char c;

    str = NULL;
    c = 10;
    while ((str = get_next_line(0)))
        if (str && strcmp(str, name) == 0) {
            free(str);
            close(i[1]);
            return i[0];
        }
        else {
            write(i[1], str, strlen(str));
            write(i[1], &c, 1);
            free(str);
            my_putstr(isatty(0) ? "> " : "");
        }
    close(i[1]);
    return i[0];
}
