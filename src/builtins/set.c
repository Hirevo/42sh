/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** set
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int disp_vars(shell_t *shell)
{
    int i;

    i = -1;
    if (shell->vars)
        while (shell->vars[++i]) {
            my_putstr(shell->vars[i]);
            my_putchar(0xa);
        }
    return 0;
}

int set(shell_t *shell, int args)
{
    char *str;
    char *comp = NULL;
    int i;
    int ret;

    if (args == 1)
        return disp_vars(shell);
    else {
        ret = 0;
        i = 0;
        while (shell->cur->av[++i]) {
            if ((str = strdup(shell->cur->av[i])) == NULL ||
                (comp = strsep(&str, "=")) == NULL)
                handle_error("calloc");
            if (check_env_error("set", comp))
                ret = 1;
            else
                add_var(shell, comp, str);
            free(comp);
        }
    }
    return ret;
}
