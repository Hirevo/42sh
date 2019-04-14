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
    if (args == 1 && strcmp(shell->cur->av[0], "unsetenv") == 0)
        return eputstr("unsetenv: Too few arguments.\n"), 1;
    else if (strcmp(shell->cur->av[0], "unsetenv") == 0)
        return unset_env(shell->cur->av);
    else
        return eputstr("%s: Too many arguments.\n", shell->cur->av[0]), 1;
}
