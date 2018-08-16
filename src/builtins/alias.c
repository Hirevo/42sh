/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** alias
*/

#include "shell.h"

int alias(shell_t *shell, int args)
{
    if (args == 1)
        return disp_all_alias(shell);
    else if (args == 2)
        return disp_alias(shell, shell->cur->av[1]);
    else if (args >= 3)
        return (add_alias(
            shell, shell->cur->av[1], construct_alias(shell->cur->av + 2)));
    return 1;
}
