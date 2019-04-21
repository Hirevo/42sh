/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unsetenv
*/

#include "my.h"
#include "shell.h"

int unsetenv_b(Shell *shell, vec_t *args)
{
    (void)(shell);
    if (lvec_size(args) == 1)
        return eputstr("unsetenv: Too few arguments.\n"), 1;
    else
        return unset_env(args);
}
