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
    char *str;

    (void)config;
    (void)arg;
    my_putstr("Configuration finished\n");
    str = my_strcatdup(BASE_RESP, "quit");
    write_client(client, str);
    free(str);
}
