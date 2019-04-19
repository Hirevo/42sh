/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** alias
*/

#include "shell.h"

int alias_b(shell_t *shell, vec_t *args)
{
    size_t count = lvec_size(args);
    if (count == 1)
        return disp_all_alias(shell);
    else if (count == 2)
        return disp_alias(shell, lvec_at(args, 1));
    else if (count >= 3)
        return add_alias(shell, lvec_at(args, 1),
            construct_alias((char **)(args->arr + 2)));
    return 1;
}
