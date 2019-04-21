/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec
*/

#include "shell.h"
#include <errno.h>

int exec_b(Shell *shell, vec_t *args)
{
    (void)(shell);
    free(lvec_pop_front(args));
    exec_process(args);
    return 0;
}
