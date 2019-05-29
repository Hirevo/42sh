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

int buffer_input(char *name, int fds[2])
{
    char *str = NULL;
    char c = 10;

    while ((str = get_next_line(0))) {
        if (str && strcmp(str, name) == 0) {
            free(str);
            close(fds[1]);
            return fds[0];
        } else {
            write(fds[1], str, strlen(str));
            write(fds[1], &c, 1);
            free(str);
            if (isatty(0)) {
                writestr("> ");
            }
        }
    }
    close(fds[1]);
    return fds[0];
}
