/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env2
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int disp_env(void)
{
    int i;

    i = -1;
    while (environ[++i] != NULL)
        printf("%s\n", environ[i]);
    return 0;
}

int check_env_error(char *mod, char *name)
{
    if (name[0] == 0 ||
        ((name[0] < 'a' || name[0] > 'z') && (name[0] < 'A' || name[0] > 'Z')))
        return (dprintf(2, "%s: Variable name must \
begin with a letter.\n",
            mod));
    if (!is_char_alpha(name))
        return (dprintf(2, "%s: Variable name must \
contain alphanumeric characters.\n",
            mod));
    return 0;
}
