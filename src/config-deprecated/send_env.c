/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** send_env
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdlib.h>

static int get_len(char *str)
{
    int ret = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] == '\\')
            ret += 1;
        ret += 1;
        i += 1;
    }
    return ret;
}

char *encode_bs(char *str)
{
    char *ret = calloc(get_len(str) + 1, sizeof(char));
    int i = 0;
    int j = 0;

    if (ret == NULL)
        return NULL;
    ret[get_len(str)] = '\0';
    while (str[i]) {
        ret[j] = str[i];
        if (str[i] == '\\') {
            j += 1;
            ret[j] = '\\';
        }
        j += 1;
        i += 1;
    }
    free(str);
    return ret;
}

void send_env(t_socket client, t_config *config, char **arg)
{
    char *send = strdup("[");
    int i = 0;

    (void)(config);
    (void)(arg);
    while (environ[i]) {
        send = my_fstrcat(send, "\"", 1);
        send = my_fstrcat(send, environ[i], 1);
        send = my_fstrcat(send, "\"", 1);
        if (environ[i + 1])
            send = my_fstrcat(send, ",\n", 1);
        i += 1;
    }
    send = my_fstrcat(send, "]", 1);
    send = encode_bs(send);
    write_client(client, HEAD_RESP);
    write_client(client, "Content-type: application/json\r\n\r\n");
    write_client(client, send);
    free(send);
}
