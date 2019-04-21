/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parserll
*/

#include "get_next_line.h"
#include "my.h"
#include "parser_ll.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int parserll_b(Shell *shell, int args)
{
    (void)(shell);
    (void)(args);
    my_putstr("Type a shell command (no worries, it won't get executed): ");
    char *str = get_next_line(0);
    t_ast *ret = parser_ll(str);
    free(str);
    return ret == 0;
}
