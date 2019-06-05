/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt_serv
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

static void exc_cmd(t_socket sock, char **str, int *nb_char)
{
    int sauv;
    int sauv2;
    Shell shell;

    (void)nb_char;
    init_shell(&shell);
    if ((sauv = dup(1)) == -1)
        return;
    if ((sauv2 = dup(2)) == -1)
        return;
    if (dup2(sock, 1) == -1)
        return;
    if (dup2(sock, 2) == -1)
        return;
    exec_line(&shell, strdup(*str + 25), false);
    dup2(sauv, 1);
    dup2(sauv2, 2);
}

void prompt_serv(t_socket sock, char c, char **prompt, int *nb_char)
{
    if (c == 13) {
        write_client(sock, "OK");
        exc_cmd(sock, prompt, nb_char);
        *prompt = strdup("(\e[32;1mDualCast\e[0m) $> ");
        *nb_char = strlen(*prompt);
        putstr("\n%s", *prompt);
        fflush(stdout);
        return;
    }
    if (c >= 32 && c <= 126)
        add_char_dc(prompt, c, nb_char);
    else if (c == 127)
        del_last_char(25, prompt, nb_char);
    del_prompt(*nb_char);
    putstr("\r%s", *prompt);
    fflush(stdout);
    write_client(sock, "OK");
    return;
}
