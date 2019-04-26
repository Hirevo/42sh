/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exit
*/

#include "my.h"
#include "shell.h"

int exit_b(Shell *shell, vec_t *args)
{
    if (lvec_size(args) == 2) {
        char *arg = lvec_at(args, 1);
        if (my_str_isnum(arg) && arg[0] != '-') {
            shell->is_done = 1;
            return get_unsigned_int(arg);
        } else {
            eputstr("exit: invalid exit code.\n");
            return 1;
        }
    } else if (lvec_size(args) == 1) {
        shell->is_done = 1;
        return shell->exit_code;
    } else {
        eputstr("exit: invalid syntax.\n");
        return 1;
    }
    return 1;
}
