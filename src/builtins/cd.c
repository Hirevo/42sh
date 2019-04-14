/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cd
*/

#include "shell.h"

int cd_b(shell_t *shell, int args)
{
    char *str;
    int i;

    i = move_dir(shell->cur->av, args);
    str = get_alias_cmd(shell, "cwdcmd");
    if (str)
        quick_exec(shell, str);
    return i;
}
