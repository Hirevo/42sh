/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins
*/

#pragma once

#include "shell.h"
#include <stdio.h>

typedef int (*builtin_func)(shell_t *, vec_t *);

int alias_b(shell_t *, vec_t *);
int builtins_b(shell_t *, vec_t *);
int cd_b(shell_t *, vec_t *);
int config_b(shell_t *, vec_t *);
int dualcast_b(shell_t *, vec_t *);
int echo_b(shell_t *, vec_t *);
int env_b(shell_t *, vec_t *);
int exec_b(shell_t *, vec_t *);
int exit_b(shell_t *, vec_t *);
int history_b(shell_t *, vec_t *);
int parserll_b(shell_t *, vec_t *);
int prompt_b(shell_t *, vec_t *);
int set_b(shell_t *, vec_t *);
int setenv_b(shell_t *, vec_t *);
int unalias_b(shell_t *, vec_t *);
int unset_b(shell_t *, vec_t *);
int unsetenv_b(shell_t *, vec_t *);
int where_b(shell_t *, vec_t *);
int which_b(shell_t *, vec_t *);
