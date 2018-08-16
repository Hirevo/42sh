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

int call_parser_ll(shell_t *shell, int args)
{
    char *str;

    (void)(shell);
    (void)(args);
    my_putstr("Type a CMD and see the Tree: ");
    str = get_next_line(0);
    if (!parser_ll(str)) {
        free(str);
        return 1;
    }
    free(str);
    return 0;
}
