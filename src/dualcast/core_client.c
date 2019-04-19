/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** core_client
*/

#include "get_next_line.h"
#include "shell.h"
#include "my.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int init_select_dc(t_socket *com, fd_set *rdfs)
{
    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    FD_SET(*com, rdfs);
    if ((select(*com + 1, rdfs, NULL, NULL, NULL)) == -1)
        return 1;
    return 0;
}

static void treat_serv_resp(
    t_client *cli, char *str, char **prompt, int *nb_char)
{
    char *tmp;

    if (str && lstr_equals(str, "OK") == false) {
        del_prompt(*nb_char);
        putstr("\r%s", str);
        fflush(stdout);
        tmp = my_strcatdup("cmd:", str);
        write_socket(cli->sock, tmp);
        free(tmp);
        *prompt = get_prompt_cli(cli);
        *nb_char = strlen(*prompt);
        putstr(*prompt);
        fflush(stdout);
    }
}

static int read_term(t_client *cli, char **prompt, int *nb_char)
{
    char c = getch_c();

    if (c == 13) {
        *prompt = get_prompt_cli(cli);
        *nb_char = strlen(*prompt);
        putstr("\n%s", *prompt);
        fflush(stdout);
    }
    if (c == 3) {
        putstr("\n");
        return 1;
    }
    if (c >= 32 && c <= 126)
        add_char_dc(prompt, c, nb_char);
    else if (c == 127)
        del_last_char(cli->len_prompt, prompt, nb_char);
    del_prompt(*nb_char);
    putstr("\r%s", *prompt);
    fflush(stdout);
    send_char(cli->sock, c);
    return 0;
}

static int read_sock(t_client *cli, char **prompt, int *nb_char)
{
    char *buf;
    int len = read_socket(cli->sock, &buf);

    if (len == 0) {
        putstr("You've been disconnected.\n");
        return 1;
    }
    else
        treat_serv_resp(cli, buf, prompt, nb_char);
    free(buf);
    return 0;
}

int core_client_dc(t_client *cli)
{
    int stop = 0;
    char *prompt = get_prompt_cli(cli);
    int nb_char = strlen(prompt);
    fd_set rdfs;
    struct termios orig_termios;

    putstr(prompt);
    fflush(stdout);
    while (!stop) {
        set_conio_terminal_mode(&orig_termios);
        stop = init_select_dc(&(cli->sock), &rdfs);
        reset_terminal_mode(&orig_termios);
        if (FD_ISSET(STDIN_FILENO, &rdfs))
            stop = read_term(cli, &prompt, &nb_char);
        else if (FD_ISSET(cli->sock, &rdfs))
            stop = read_sock(cli, &prompt, &nb_char);
    }
    return 0;
}
