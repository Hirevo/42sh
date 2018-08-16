/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** comment
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

int clear_comment(shell_t *shell)
{
    int i;
    int quote;
    char *tmp;

    i = 0;
    quote = 0;
    while (shell->line[i]) {
        if (shell->line[i] == '\'' && (quote == 0 || quote == 1))
            quote = (quote == 0) ? 1 : 0;
        if (shell->line[i] == '"' && (quote == 0 || quote == 2))
            quote = (quote == 0) ? 2 : 0;
        if (shell->line[i] == '#' && quote == 0 &&
            (i == 0 || (i != 0 && (shell->line[i - 1] == ' ')))) {
            tmp = my_strndup(shell->line, i);
            free(shell->line);
            shell->line = tmp;
            return 0;
        }
        i += 1;
    }
    return 0;
}
