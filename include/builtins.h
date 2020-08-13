/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins
*/

#pragma once

#include "shell.h"
#include <stdio.h>

typedef int (*builtin_func)(Shell *, vec_t *);

int alias_b(Shell *, vec_t *);
int builtins_b(Shell *, vec_t *);
int cd_b(Shell *, vec_t *);
int config_b(Shell *, vec_t *);
int dualcast_b(Shell *, vec_t *);
int echo_b(Shell *, vec_t *);
int env_b(Shell *, vec_t *);
int exec_b(Shell *, vec_t *);
int exit_b(Shell *, vec_t *);
int expand_b(Shell *, vec_t *);
int history_b(Shell *, vec_t *);
int parserll_b(Shell *, vec_t *);
int prompt_b(Shell *, vec_t *);
int set_b(Shell *, vec_t *);
int setenv_b(Shell *, vec_t *);
int unalias_b(Shell *, vec_t *);
int unset_b(Shell *, vec_t *);
int unsetenv_b(Shell *, vec_t *);
int where_b(Shell *, vec_t *);
int which_b(Shell *, vec_t *);
