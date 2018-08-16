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
    if (args > 2 ||
        (args == 2 &&
            (shell->cur->av[1][0] < '0' || shell->cur->av[1][0] > '9') &&
            shell->cur->av[1][0] != '-'))
        my_print_err("exit: Expression Syntax.\n");
    else if (args == 2 && !my_str_isnum(shell->cur->av[1] + 1))
        my_print_err("exit: Badly Formed Number.\n");
    else {
        shell->is_done = 1;
        shell->exit_code = ((args == 2) ? get_unsigned_int(shell->cur->av[1]) :
                                          shell->exit_code);
        return shell->exit_code;
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
