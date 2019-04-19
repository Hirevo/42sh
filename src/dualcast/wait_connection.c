/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** wait_connection
*/

#include "get_next_line.h"
#include "shell.h"
#include "my.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

static char *read_code(t_socket client)
{
    char *ret = calloc(5, sizeof(char));
    int len;

    if (ret == NULL)
        return NULL;
    len = recv(client, ret, 4, 0);
    if (len < 0)
        return NULL;
    ret[len] = '\0';
    return ret;
}

static void send_login(t_socket sock)
{
    char *login = getenv("LOGNAME");
    char *str;

    if (login) {
        str = my_fstrcat("OK:", login, 0);
        if (str) {
            write_socket(sock, str);
            free(str);
        }
    }
    else
        write_socket(sock, "OK:");
}

static int new_client_dc(
    t_socket sock, fd_set *rdfs, t_socket *client, char *passwd)
{
    t_sockaddr_in csin;
    socklen_t len = sizeof(csin);
    char *recv_code;

    *client = accept(sock, (struct sockaddr *)(&csin), &len);
    if (*client == -1) {
        close(*client);
        return 0;
    }
    FD_SET(*client, rdfs);
    recv_code = read_code(*client);
    if (!strcmp(recv_code, passwd)) {
        putstr("Connected.\n");
        send_login(*client);
        return 1;
    }
    putstr("Connection failed.\n");
    send(*client, "KO", 2, 0);
    close(*client);
    return 0;
}

t_socket wait_connection(t_socket sock, fd_set *rdfs, char *passwd)
{
    t_socket client;
    int stop;

    stop = 0;
    client = 8;
    while (!stop) {
        FD_ZERO(rdfs);
        FD_SET(STDIN_FILENO, rdfs);
        FD_SET(sock, rdfs);
        FD_SET(client, rdfs);
        if (select(sock + 1, rdfs, NULL, NULL, NULL) == -1)
            return -1;
        if (FD_ISSET(STDIN_FILENO, rdfs))
            stop = 2;
        else if (FD_ISSET(sock, rdfs))
            stop = new_client_dc(sock, rdfs, &client, passwd);
    }
    if (stop == 2) {
        close(sock);
        free(get_next_line(0));
        return -1;
    }
    return client;
}
