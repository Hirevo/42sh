/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** comment
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

OPTION(CharPtr) clear_comment(char *line)
{
    bool quoted = false;
    char *tmp;

    for (size_t cur = 0; line[cur]; cur++) {
        if (line[cur] == '\\') {
            cur += !!(line[cur + 1]);
        } else if (line[cur] == '$' && line[cur + 1] == '#') {
            cur += 1;
        } else if (line[cur] == '\'') {
            cur += 1;
            while (line[cur] && line[cur] != '\'') {
                cur += 1;
            }
            cur -= (line[cur] == 0);
        } else if (line[cur] == '"') {
            quoted = !quoted;
        } else if (line[cur] == '#' && quoted == false) {
            tmp = strndup(line, cur);
            free(line);
            return SOME(CharPtr, tmp);
        }
    }
    return SOME(CharPtr, line);
}
