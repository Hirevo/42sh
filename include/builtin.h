/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtin
*/

#pragma once

#include "shell.h"
#include <stdio.h>

typedef struct parse_env_s {
    int ignore;
    int null;
    int unset;
    char **unset_l;
    char **cmd;
} parse_env_t;

int alias(shell_t *, vec_t *);
int cd_b(shell_t *, vec_t *);
int config_b(shell_t *, vec_t *);
int dualcast_b(shell_t *, vec_t *);
int echo_b(shell_t *, vec_t *);
int exit_b(shell_t *, vec_t *);
int exec_b(shell_t *, vec_t *);
int setenv_b(shell_t *, vec_t *);
int unalias_b(shell_t *, vec_t *);
int unsetenv_b(shell_t *, vec_t *);
int prompt(shell_t *, vec_t *);
int env_b(shell_t *, vec_t *);
int call_parser_ll(shell_t *, vec_t *);
parse_env_t *parse_env(vec_t *);

/*
** check_file.c
*/
int print_error_path(char *);
int print_error(char *);

/*
** check_file_2.c
*/
int is_folder(char *);

/*
** env.c
*/
void show_tab_env(char **);

/*
** env_checkerror.c
*/
int cherror_env_parse(vec_t *);

/*
** env_cherror.c
*/
int is_alpha_err(char *, int);

/*
** launch_soft.c
*/
int launch_soft(parse_env_t *);

/*
** shw_env_parse;
*/
int str_in_liste(char **, char *);
void show_env_parse(parse_env_t *);

/*
** show_signal.c
*/

int show_signal(int);

/*
** where.c
*/

int where(shell_t *, vec_t *);

/*
** which.c
*/

int which(shell_t *, vec_t *);
