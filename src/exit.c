/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exit
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

int check_exit(shell_t *shell, int args)
{
    if (args == 2) {
        char *arg = shell->cur->av[1];
        if (my_str_isnum(arg) && arg[0] != '-') {
            shell->is_done = 1;
            return get_unsigned_int(arg);
        } else {
            eputstr("exit: invalid exit code.\n");
            return 1;
        }
    } else if (args == 1) {
        shell->is_done = 1;
        return shell->exit_code;
    } else {
        eputstr("exit: invalid syntax.\n");
        return 1;
    }
    return 1;
}
