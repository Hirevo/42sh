/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** connect
*/

#include "get_next_line.h"
#include "shell.h"
#include "server.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_code(char *code)
{
    int i;

    if (strlen(code) != 4)
        return 0;
    i = 0;
    while (code[i]) {
        if (code[i] < '0' || code[i] > '9')
            return 0;
        i += 1;
    }
    return 1;
}

static int check_correct_passwd(t_client *cli)
{
    char *ret;

    read_socket(cli->sock, &ret);
    if (lstr_starts_with(ret, "OK:")) {
        cli->name = strdup(ret + 3);
        free(ret);
        return 1;
    }
    free(ret);
    return 0;
}

static int send_passwd(t_client *cli)
{
    char *code;

    putstr("Enter session token: ");
    fflush(stdout);
    if ((code = get_next_line(0)) == NULL) {
        close(cli->sock);
        return 0;
    }
    if (!is_valid_code(code)) {
        putstr("Invalid session token format.\n");
        close(cli->sock);
        return 0;
    }
    if (send(cli->sock, code, strlen(code), 0) < 0) {
        close(cli->sock);
        return 0;
    }
    if (check_correct_passwd(cli))
        return 1;
    putstr("Invalid session token.\n");
    return 0;
}

int init_connect_dc(char *addr, t_client *cli)
{
    t_sockaddr_in sin;
    struct hostent *hostinfo;

    if ((cli->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return 1;
    if ((hostinfo = gethostbyname(addr)) == NULL)
        return eputstr("Could not find host '%s'.\n", addr), 1;
    sin.sin_addr = *(t_in_addr *)hostinfo->h_addr;
    sin.sin_port = htons(DUALCAST_PORT);
    sin.sin_family = AF_INET;
    if (connect(cli->sock, (t_sockaddr *)&sin, sizeof(t_sockaddr)) == -1)
        return eputstr("Could not connect to '%s'.\n", addr), 1;
    if (send_passwd(cli))
        return 0;
    close(cli->sock);
    return 1;
}
