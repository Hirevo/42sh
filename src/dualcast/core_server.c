/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** core_server
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int init_client_dc(fd_set *rdfs, t_socket *sock, t_socket *client)
{
    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    FD_SET(*sock, rdfs);
    FD_SET(*client, rdfs);
    if (select(*client + 1, rdfs, NULL, NULL, NULL) == -1) {
        perror("select ");
        return 3;
    }
    return 0;
}

int new_client_dc(t_socket sock)
{
    t_sockaddr_in csin;
    socklen_t sinsize;
    t_socket csock;

    sinsize = sizeof(csin);
    if ((csock = accept(sock, (t_sockaddr *)&csin, &sinsize)) ==
        SOCKET_ERROR) {
        perror("");
        return 1;
    }
    close(csock);
    return 0;
}

static int client_talk_dc(
    t_socket client, fd_set *rdfs, char **prompt, int *nb_char)
{
    int len;
    char *buf;

    if (FD_ISSET(client, rdfs)) {
        len = read_socket(client, &buf);
        if (len == 0) {
            close(client);
            return 1;
        } else {
            response_serv(client, buf, prompt, nb_char);
        }
    }
    return 0;
}

int core_server_dc(t_socket sock, t_socket client, fd_set *rdfs)
{
    char *prompt = strdup("(\e[32;1mDualCast\e[0m) $> ");
    int nb_char = prompt ? strlen(prompt) : 0;
    int stop = 0;

    if (prompt == 0)
        return 1;
    putstr(prompt);
    fflush(stdout);
    while (!stop) {
        stop = init_client_dc(rdfs, &sock, &client);
        if (FD_ISSET(STDIN_FILENO, rdfs) && !stop)
            stop = 2;
        else if (FD_ISSET(sock, rdfs) && !stop)
            new_client_dc(sock);
        else if (!stop)
            stop = client_talk_dc(client, rdfs, &prompt, &nb_char);
    }
    if (FD_ISSET(STDIN_FILENO, rdfs))
        free(get_next_line(0));
    return 0;
}
