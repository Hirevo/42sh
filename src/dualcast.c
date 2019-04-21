/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** dualcast
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int launch_dc_server(void)
{
    fd_set rdfs;
    t_socket socket;
    t_socket client;
    char *code;

    if ((code = get_password()) == NULL)
        return 1;
    if (init_dualcast(&socket) == -1)
        return 1;
    putstr("Dualcast ready !\n"
           "Here is the session token: %s\n"
           "Waiting for a client...\n",
        code);
    if ((client = wait_connection(socket, &rdfs, code)) == -1)
        return 1;
    core_server_dc(socket, client, &rdfs);
    free(code);
    close(client);
    close(socket);
    putstr("End of session.\n");
    return 0;
}

static int launch_dc_client(char *addr)
{
    t_client client;

    if (init_connect_dc(addr, &client))
        return 1;
    if (strlen(client.name) == 0)
        client.name = NULL;
    core_client_dc(&client);
    close(client.sock);
    free(client.name);
    return 0;
}

int launch_dualcast(Shell *shell, vec_t *args)
{
    (void)(shell);
    if (lvec_size(args) >= 2 && lstr_equals(lvec_at(args, 1), "start"))
        launch_dc_server();
    else if (lvec_size(args) >= 3 && lstr_equals(lvec_at(args, 1), "connect"))
        launch_dc_client(lvec_at(args, 2));
    else
        putstr("Usage: %s [start | connect endpoint_uri]\n", lvec_front(args));
    return 0;
}
