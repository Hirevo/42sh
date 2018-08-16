/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** com_serv
*/

#include "my.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

int read_client(t_socket sock, char *buffer)
{
    int n = recv(sock, buffer, BUF_SIZE - 1, 0);

    if (n < 0) {
        perror("recv");
        n = 0;
    }
    buffer[n] = 0;
    return n;
}

void write_client(t_socket sock, char *buffer)
{
    if (send(sock, buffer, strlen(buffer), 0) < 0)
        perror("send");
}
