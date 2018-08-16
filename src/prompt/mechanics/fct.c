/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fct
*/

#include "shell.h"

void get_cur_fcts(void (*cur_fct[6])(shell_t *))
{
    cur_fct[0] = move_backw;
    cur_fct[1] = move_forw;
    cur_fct[2] = move_upw;
    cur_fct[3] = move_downw;
    cur_fct[4] = move_home;
    cur_fct[5] = move_end;
}
