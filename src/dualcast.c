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
    printf("DualCast ready\nYour session token is : %s\n", code);
    if ((client = wait_connection(socket, &rdfs, code)) == -1)
        return 1;
    core_server_dc(socket, client, &rdfs);
    free(code);
    close(client);
    close(socket);
    printf("End of session\n");
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

int launch_dualcast(shell_t *shell, int args)
{
    if (args >= 2 && !strcmp(shell->cur->av[1], "start"))
        launch_dc_server();
    else if (args >= 3 && !strcmp(shell->cur->av[1], "connect"))
        launch_dc_client(shell->cur->av[2]);
    else
        printf("Usage : dualcast [start | connect addr_ip]\n");
    return 0;
}
