/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** config
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int init_client(
    fd_set *rdfs, int actual, t_socket sock, t_socket *clients)
{
    int i = 0;

    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    FD_SET(sock, rdfs);
    while (i < actual) {
        FD_SET(clients[i], rdfs);
        i += 1;
    }
    if (select(MAX_CLIENTS + 1, rdfs, NULL, NULL, NULL) == -1) {
        perror("select ");
        return 1;
    }
    return 0;
}

static void clear_clients(t_socket *clients, int actual)
{
    int i;

    i = 0;
    while (i < actual) {
        closesocket(clients[i]);
        i += 1;
    }
}

static int core(t_socket sock, t_config *config, int actual)
{
    int stop;
    t_socket clients[MAX_CLIENTS];
    fd_set rdfs;

    stop = 0;
    while (!stop) {
        init_client(&rdfs, actual, sock, clients);
        if (FD_ISSET(STDIN_FILENO, &rdfs))
            stop = 2;
        else if (FD_ISSET(sock, &rdfs))
            new_client(clients, &actual, &rdfs, sock);
        else
            stop = client_talk(clients, &actual, &rdfs, config);
    }
    if (stop == 2)
        free(get_next_line(0));
    writestr("server closed\n");
    clear_clients(clients, actual);
    closesocket(sock);
    return 0;
}

int config_http(Shell *shell, t_config *config)
{
    int port;
    t_socket serv;
    char *ip;

    srand(getpid() * time(NULL));
    if ((port = init_connection(&serv)) == -1)
        return 1;
    putstr("server started on http://localhost:%d/\n", port);
    ip = lstr_concat(strdup("open 'http://localhost:"), 2, LSTR_INT,
        (int)(port), LSTR_CHAR, '\'');
    quick_exec(shell, ip);
    core(serv, config, 0);
    close(serv);
    return 0;
}
