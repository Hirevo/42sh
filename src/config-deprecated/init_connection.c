/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** init_connection
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>

int init_connection(t_socket *sock)
{
    int port;
    t_sockaddr_in sin;

    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("socket()");
        return -1;
    }
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons((port = (rand() % 65535)));
    sin.sin_family = AF_INET;
    while (bind(*sock, (t_sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
        sin.sin_port = htons((port = (rand() % 65535)));
    }
    if (listen(*sock, MAX_CLIENTS) == SOCKET_ERROR) {
        perror("listen()");
        return -1;
    }
    return port;
}
