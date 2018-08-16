/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** add_env_http
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdlib.h>

void add_env_http(t_socket client, t_config *config, char **arg)
{
    char *decode;

    (void)(config);
    if (nb_args(arg) >= 5) {
        if (getenv(arg[3])) {
            write_client(client, ERROR_RESP);
            return;
        }
        if (nb_args(arg) == 6) {
            decode = calloc(strlen(arg[5]) + 1, sizeof(char));
            if (decode == NULL)
                return;
            urldecode(arg[5], decode);
            set_env(arg[3], decode);
            free(decode);
        }
        else if (nb_args(arg) == 5)
            set_env(arg[3], "");
        write_client(client, BASE_RESP);
        write_client(client, "add_env_ok");
    }
    else
        write_client(client, ERROR_RESP);
}

void del_env_http(t_socket client, t_config *config, char **arg)
{
    (void)(config);
    unsetenv(arg[3]);
    write_client(client, BASE_RESP);
    write_client(client, "del_env_ok");
}

void update_env_http(t_socket client, t_config *config, char **arg)
{
    char *decode;

    (void)(config);
    if (nb_args(arg) >= 5) {
        if (nb_args(arg) == 6) {
            decode = calloc(strlen(arg[5]) + 1, sizeof(char));
            if (decode == NULL)
                return;
            urldecode(arg[5], decode);
            set_env(arg[3], decode);
        }
        write_client(client, BASE_RESP);
        write_client(client, "update_env_ok");
    }
    else
        write_client(client, ERROR_RESP);
}
