/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** response_serv
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

static void print_cmd(char *buf, char **prompt, int *nb_char)
{
    del_prompt(*nb_char);
    putstr("\r%s", buf + 4);
    *prompt = strdup("(\e[32;1mDualCast\e[0m) $> ");
    *nb_char = strlen(*prompt);
    putstr("%s", *prompt);
    fflush(stdout);
}

int response_serv(t_socket sock, char *buf, char **prompt, int *nb_char)
{
    if (lstr_starts_with(buf, "char:"))
        prompt_serv(sock, buf[5], prompt, nb_char);
    if (lstr_starts_with(buf, "cmd:"))
        print_cmd(buf, prompt, nb_char);
    free(buf);
    return 0;
}
