/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exit
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdlib.h>

void exit_config(t_socket client, t_config *config, char **arg)
{
    (void)config;
    (void)arg;
    writestr("Configuration finished\n");
    char *str = fmtstr(BASE_RESP "%s", "quit");
    write_client(client, str);
    free(str);
}
