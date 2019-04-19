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

exec_status_t exec_builtins(shell_t *shell, vec_t *args)
{
    builtin_func func = lhmap_get(shell->builtins, lvec_front(args));
    if (func != 0) {
        return (exec_status_t){
            .ok = true,
            .code = func(shell, args),
        };
    } else {
        return (exec_status_t){
            .ok = false,
            .code = 1,
        };
    }
}
