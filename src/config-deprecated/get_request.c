/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_request
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdlib.h>

static const char *request_tab[] = {
    "quit",
    "get_env",
    "get_info",
    "add_env",
    "update_env",
    "del_env",
    "exec",
    "get_prompt_sel",
    "update_prompt_sel",
    NULL,
};

int nb_request(void)
{
    int i = 0;

    while (request_tab[i])
        i += 1;
    return i;
}

int indexof_request(char *str)
{
    int i = 0;

    while (request_tab[i]) {
        if (!strcmp(str, (char *)request_tab[i]))
            return i;
        i += 1;
    }
    return -1;
}

void get_tab_request(void (**request_tab)(t_socket, t_config *, char **))
{
    request_tab[0] = &exit_config;
    request_tab[1] = &send_env;
    request_tab[2] = &send_info;
    request_tab[3] = &add_env_http;
    request_tab[4] = &update_env_http;
    request_tab[5] = &del_env_http;
    request_tab[6] = &exec_cmd_http;
    request_tab[7] = &send_prompt_sel;
    request_tab[8] = &update_prompt_sel;
}
