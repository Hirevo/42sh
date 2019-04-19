/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env
*/

#include "shell.h"

int env_b(shell_t *shell, vec_t *args)
{
    (void)(shell);
    if (lvec_size(args) == 1) {
        for (size_t i = 0; environ && environ[i]; i++)
            putstr("%s\n", environ[i]);
    } else {
        eputstr("env: too many arguments.\n");
    }
    return 0;
}
