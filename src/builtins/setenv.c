/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** setenv
*/

#include "my.h"
#include "shell.h"

int setenv_b(shell_t *shell, int args)
{
    int r;

    r = 0;
    if (args == 3 && strcmp(shell->cur->av[0], "setenv") == 0)
        r = set_env(shell->cur->av[1], shell->cur->av[2]);
    else if (args == 1 && strcmp(shell->cur->av[0], "setenv") == 0)
        r = disp_env();
    else if (args == 2 && strcmp(shell->cur->av[0], "setenv") == 0)
        r = set_env(shell->cur->av[1], "");
    else
        r = my_print_err(shell->cur->av[0]) +
            my_print_err(": Too many arguments.\n") - 1;
    reload_shell(shell);
    return r;
}
