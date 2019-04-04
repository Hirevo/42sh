/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env_checkerr
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"

static int is_an_arg(char *str)
{
    if (!strcmp(str, "-i") || !strcmp(str, "--ignore-environment"))
        return 1;
    if (!strcmp(str, "-0") || !strcmp(str, "--null"))
        return 1;
    if (!strcmp(str, "-i0") || !strcmp(str, "-0i"))
        return 1;
    if (!strcmp(str, "-u") || !strncmp(str, "--unset=", 8))
        return 1;
    return 0;
}

static int check_arg(char **cmd)
{
    for (int i = 0; cmd[i] && cmd[i][0] == '-'; i++) {
        if (!is_an_arg(cmd[i]))
            return dprintf(2, "env: invalid option -- '%s'\n", cmd[i] + 1), 1;
        if (is_in_env(cmd[i], 'u') && strncmp(cmd[i], "--unset=", 8) &&
            strcmp(cmd[i], "--null"))
            i += 1;
    }
    return 0;
}

static int check_len_arg(char **cmd)
{
    int i;

    i = 1;
    while (cmd[i] && cmd[i][0] == '-') {
        if (strlen(cmd[i]) == 1) {
            dprintf(2, "env : invalid option -- ''\n");
            return 1;
        }
        if (strcmp(cmd[i], "-u") == 0) {
            i += 1;
            if (!cmd[i]) {
                dprintf(2, "env: option requires an argument -- 'u'\n");
                return 1;
            }
        }
        i += 1;
    }
    return 0;
}

static int check_unset(char **cmd)
{
    int i;

    i = 0;
    while (++i && cmd[i] && cmd[i][0] == '-') {
        if (strncmp(cmd[i], "--unset=", 8) == 0) {
            if (strlen(cmd[i]) == 8) {
                dprintf(2, "env: cannot unset '': Invalid argument\n");
                return 1;
            }
            if (is_alpha_err(cmd[i], 8))
                return 1;
        }
        else if (is_in_env(cmd[i], 'u') && strcmp(cmd[i], "--null")) {
            i += 1;
            if (is_alpha_err(cmd[i], 0))
                return 1;
        }
    }
    return 0;
}

int cherror_env_parse(char **cmd)
{
    if (check_len_arg(cmd))
        return 1;
    if (check_arg(cmd))
        return 1;
    if (check_unset(cmd))
        return 1;
    return 0;
}
