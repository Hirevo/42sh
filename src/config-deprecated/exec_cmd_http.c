/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec_cmd_http
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char *get_cmd_exc(char *cmd_path, char *cmd)
{
    char *tmp;

    if (cmd_path && !strcmp(cmd_path, "emacs"))
        return strdup(cmd);
    else {
        tmp = my_strcatdup("timeout 1 ", cmd);
        return tmp;
    }
}

static int execute_http(t_socket client, char *cmd)
{
    shell_t shell;
    int sauv;
    int sauv2;

    init_shell(&shell);
    shell.line = cmd;
    sauv = dup(1);
    if (sauv == -1)
        return 1;
    sauv2 = dup(2);
    if (sauv2 == -1)
        return 1;
    if (dup2(client, 1) == -1)
        return 1;
    if (dup2(client, 2) == -1)
        return 1;
    exec_line(&shell, 0);
    dup2(sauv, 1);
    dup2(sauv2, 2);
    close(sauv);
    close(sauv2);
    return 0;
}

static int change_dir_http(t_socket client, char **cmd_p)
{
    if (nb_args(cmd_p) >= 2) {
        if (chdir(cmd_p[1]) == -1)
            write_client(client, strerror(errno));
        else {
            write_client(client, "Change to ");
            write_client(client, cmd_p[1]);
        }
    }
    else
        write_client(client, "Error: precise a folder");
    return 0;
}

void exec_cmd_http(t_socket client, t_config *config, char **arg)
{
    char *cmd;
    char **cmd_p;

    (void)config;
    if (nb_args(arg) >= 4) {
        cmd = calloc(strlen(arg[3]) + 1, sizeof(char));
        if (cmd == NULL)
            return;
        urldecode(arg[3], cmd);
        cmd_p = my_split_char(cmd, ' ');
        if (cmd_p == NULL)
            return;
        write_client(client, BASE_RESP);
        if (!strcmp(cmd_p[0], "cd"))
            change_dir_http(client, cmd_p);
        else
            execute_http(client, cmd);
    }
    else
        write_client(client, ERROR_RESP);
}
