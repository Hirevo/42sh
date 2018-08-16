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
    printf("\r%s", buf + 4);
    *prompt = strdup("(\033[32;1mDualCast\033[0m) $> ");
    *nb_char = strlen(*prompt);
    printf("%s", *prompt);
}

int response_serv(t_socket sock, char *buf, char **prompt, int *nb_char)
{
    if (!my_strncmp(buf, "char:", 5))
        prompt_serv(sock, buf[5], prompt, nb_char);
    if (!my_strncmp(buf, "cmd:", 4))
        print_cmd(buf, prompt, nb_char);
    free(buf);
    return 0;
}
