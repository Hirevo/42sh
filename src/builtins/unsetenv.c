/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unsetenv
*/

#include "my.h"
#include "shell.h"

int unsetenv_b(shell_t *shell, int args)
{
    int r;

    r = 0;
    if (args == 1 && strcmp(shell->cur->av[0], "unsetenv") == 0)
        r = my_print_err("unsetenv: Too few arguments.\n");
    else if (strcmp(shell->cur->av[0], "unsetenv") == 0)
        r = unset_env(shell->cur->av);
    else
        r = my_print_err(shell->cur->av[0]) +
            my_print_err(": Too many arguments.\n") - 1;
    reload_shell(shell);
    return r;
}
