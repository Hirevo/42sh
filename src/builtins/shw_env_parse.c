/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** shw_env_parse
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <unistd.h>

int str_in_liste(char **str1, char *in)
{
    int i;

    i = 0;
    while (i < nb_args(str1)) {
        if (strncmp(str1[i], in, strlen(str1[i])) == 0 &&
            in[strlen(str1[i])] == '=')
            return 1;
        i += 1;
    }
    return 0;
}

void show_env_parse(parse_env_t *parse)
{
    int i;

    i = 0;
    if (parse->ignore == 1)
        return;
    else
        while (environ && environ[i]) {
            if (!str_in_liste(parse->unset_l, environ[i]))
                printf("%s", environ[i]);
            i += 1;
        }
}
