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
            my_print_err("exit: invalid exit code.\n");
            return 1;
        }
    } else if (args == 1) {
        shell->is_done = 1;
        return shell->exit_code;
    } else {
        my_print_err("exit: invalid syntax.\n");
        return 1;
    }
    return 1;
}

int set_error(shell_t *shell, int ret)
{
    shell->exit_code = ret;
    free(shell->exit_str);
    shell->exit_str = my_unsigned_to_char(ret);
    return ret;
}
