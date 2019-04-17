/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cd
*/

#include "shell.h"

int cd_b(shell_t *shell, vec_t *args)
{
    int i = move_dir(args);
    char *str = get_alias_cmd(shell, "cwdcmd");

    if (str)
        quick_exec(shell, str);
    return i;
}
