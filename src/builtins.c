/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins
*/

#include "builtins.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

OPTION(Int) exec_builtins(Shell *shell, vec_t *args)
{
    builtin_func func = lhmap_get(shell->builtins, lvec_front(args));
    if (func != 0) {
        return SOME(Int, func(shell, args));
    } else {
        return NONE(Int);
    }
}
