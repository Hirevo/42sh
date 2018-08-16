/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** print
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_print_err(char *err)
{
    write(2, err, strlen(err));
    return 1;
}

void my_print_fd(char *str, int fd)
{
    write(fd, str, strlen(str));
}

int my_print_ret(char *err, int ret)
{
    write(2, err, strlen(err));
    return ret;
}

int ret_error(shell_t *shell, char *message)
{
    shell->exit_code = 1;
    free(shell->exit_str);
    shell->exit_str = my_unsigned_to_char(1);
    printf("%s", message);
    return -1;
}
