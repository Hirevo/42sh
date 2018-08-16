/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** echo
*/

#include "shell.h"

int echo_b(shell_t *shell, int args)
{
    (void)args;
    return echo_term(shell->cur->av + 1);
}
