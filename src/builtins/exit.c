/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exit
*/

#include "shell.h"

int exit_b(shell_t *shell, vec_t *args)
{
    return check_exit(shell, args);
}
