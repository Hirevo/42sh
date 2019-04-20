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
    bool quoted = false;
    char *tmp;

    for (size_t cur = 0; shell->line[cur]; cur++) {
        if (shell->line[cur] == '\\') {
            cur += !!(shell->line[cur + 1]);
        } else if (shell->line[cur] == '\'') {
            cur += 1;
            while (shell->line[cur] && shell->line[cur] != '\'')
                cur += 1;
            cur -= (shell->line[cur] == 0);
        } else if (shell->line[cur] == '"') {
            quoted = !quoted;
        } else if (shell->line[cur] == '#' && quoted == false) {
            tmp = strndup(shell->line, cur);
            free(shell->line);
            shell->line = tmp;
            return 0;
        }
    }
    return 0;
}
