/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parse_env
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>

int nb_args_env(char **cmd)
{
    int i = 1;

    while (cmd[i] && cmd[i][0] == '-') {
        if (is_in_env(cmd[i], 'u') && strcmp(cmd[i], "--null") &&
            strncmp(cmd[i], "--unset=", 8))
            i += 1;
        i += 1;
    }
    return i;
}

static void fill_stru_2(char **cmd, parse_env_t *ret, int *i)
{
    if (is_in_env(cmd[*i], 'u')) {
        (*i) += 1;
        ret->unset_l = add_to_chardouble(cmd[*i], ret->unset_l);
        ret->unset = 1;
    }
    if (is_in_env(cmd[*i], '0'))
        ret->null = 1;
    if (is_in_env(cmd[*i], 'i'))
        ret->ignore = 1;
}

static void fill_stru_1(char **cmd, parse_env_t *ret)
{
    int i = 0;

    while (++i && cmd[i] && cmd[i][0] == '-') {
        if (strncmp(cmd[i], "--unset=", 8) == 0) {
            ret->unset_l = add_to_chardouble(cmd[i] + 8, ret->unset_l);
            ret->unset = 1;
        }
        else if (strcmp(cmd[i], "--null") == 0)
            ret->null = 1;
        else if (strcmp(cmd[i], "--ignore-environment") == 0)
            ret->ignore = 1;
        else
            fill_stru_2(cmd, ret, &i);
    }
}

parse_env_t *parse_env(char **cmd)
{
    parse_env_t *ret = calloc(1, sizeof(*ret));

    if (ret == NULL || cherror_env_parse(cmd))
        return NULL;
    ret->ignore = 0;
    ret->null = 0;
    ret->unset = 0;
    ret->unset_l = NULL;
    fill_stru_1(cmd, ret);
    ret->cmd = NULL;
    if (nb_args_env(cmd) != nb_args(cmd))
        ret->cmd = cmd + nb_args_env(cmd);
    else
        ret->cmd = NULL;
    return ret;
}
