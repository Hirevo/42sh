/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** send_info
*/

#include "my.h"
#include "server.h"
#include <stdlib.h>

static char *get_resp(t_info_pc *info)
{
    char *ret = my_fstrcat("{\"hostname\" : \"", info->hostname, 3);

    ret = my_fstrcat(ret, "\", \"os\" : \"", 1);
    ret = (info->os) ? my_fstrcat(ret, info->os, 2) : ret;
    ret = my_fstrcat(ret, "\", \"platform\" : \"", 1);
    ret = (info->plateforme) ? my_fstrcat(ret, info->plateforme, 2) : ret;
    ret = my_fstrcat(ret, "\", \"version\" : \"", 1);
    ret = (info->version) ? my_fstrcat(ret, info->version, 2) : ret;
    ret = my_fstrcat(ret, "\", \"memory_total\" : ", 1);
    ret = my_fstrcat(ret, int_toc(info->mem_total), 2);
    ret = my_fstrcat(ret, ", \"memory_available\" : ", 1);
    ret = my_fstrcat(ret, int_toc(info->mem_available), 2);
    ret = my_fstrcat(ret, ", \"process\" : \"", 1);
    ret = (info->proco) ? my_fstrcat(ret, info->proco, 2) : ret;
    return my_fstrcat(ret, "\"}", 1);
}

void send_info(t_socket client, t_config *config, char **arg)
{
    char *resp;
    t_info_pc *info = get_info();

    (void)(config);
    (void)(arg);
    if (info == NULL) {
        write_client(client, ERROR_RESP);
        return;
    }
    write_client(client, HEAD_RESP);
    write_client(client, "Content-type: application/json\r\n\r\n");
    resp = get_resp(info);
    write_client(client, resp);
    free(info);
    free(resp);
}
