/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt
*/

#include "my.h"
#include "server.h"
#include <stdlib.h>

void send_prompt_sel(t_socket client, t_config *config, char **arg)
{
    char *selected;

    (void)arg;
    if ((selected = int_toc(config->prompt)) == NULL)
        return;
    write_client(client, BASE_RESP);
    write_client(client, selected);
    free(selected);
}

void update_prompt_sel(t_socket client, t_config *config, char **arg)
{
    config->prompt = my_getnbr(arg[3]);
    write_client(client, BASE_RESP);
}
