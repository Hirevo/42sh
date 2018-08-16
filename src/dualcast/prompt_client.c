/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** prompt_client
*/

#include "my.h"
#include "server.h"
#include <string.h>

char *get_prompt_cli(t_client *client)
{
    char *ret;

    ret = strdup("(\033[32;1m");
    if (client->name) {
        ret = my_fstrcat(ret, client->name, 1);
        ret = my_fstrcat(ret, "@", 1);
    }
    ret = my_fstrcat(ret, "DualCast\033[0m) $> ", 1);
    client->len_prompt = strlen(ret);
    return ret;
}
