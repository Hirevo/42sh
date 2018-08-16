/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec_arg_2
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void exec_not_path(char *cmd, char **arg, char **ae)
{
    errno = 0;
    if (print_error(cmd) && execve(cmd, arg, ae) == -1 && errno == ENOEXEC)
        dprintf(
            2, "%s: Exec format error. Binary file not executable.\n", cmd);
}
