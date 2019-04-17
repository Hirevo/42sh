/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** echo
*/

#include "shell.h"

int echo_b(shell_t *shell, vec_t *args)
{
    (void)(shell);
    return echo_term(args);
}
