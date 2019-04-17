/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** setenv
*/

#include "my.h"
#include "shell.h"

int setenv_b(shell_t *shell, vec_t *args)
{
    size_t count = lvec_size(args);
    int r = 0;

    (void)(shell);
    if (count == 3 && strcmp(lvec_at(args, 0), "setenv") == 0)
        return set_env(lvec_at(args, 1), lvec_at(args, 2));
    else if (count == 1 && strcmp(lvec_at(args, 0), "setenv") == 0)
        return disp_env();
    else if (count == 2 && strcmp(lvec_at(args, 0), "setenv") == 0)
        return set_env(lvec_at(args, 1), "");
    else
        return eputstr("%s: too many arguments.\n", lvec_at(args, 0)), 1;
    return r;
}
