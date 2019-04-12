/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** launch_soft
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <stdlib.h>

int str_in(char *str1, char *in)
{
    if (strncmp(str1, in, strlen(str1)) == 0 && in[strlen(str1)] == '=')
        return 1;
    return 0;
}

int nb_args_valid(parse_env_t *parse)
{
    int i = 0;
    int count = 0;

    while (environ && environ[i]) {
        if (!str_in_liste(parse->unset_l, environ[i]))
            count += 1;
        i += 1;
    }
    return count;
}

char **getting_env(parse_env_t *parse, char **env)
{
    int i = 0;
    int j = 0;

    if (parse->ignore == 1)
        return NULL;
    env = calloc(nb_args_valid(parse) + 1, sizeof(char *));
    if (env == NULL)
        return NULL;
    env[nb_args_valid(parse)] = NULL;
    while (environ && environ[i]) {
        if (!str_in_liste(parse->unset_l, environ[i])) {
            env[j] = strdup(environ[i]);
            j += 1;
        }
        i += 1;
    }
    return env;
}

static int exec_arg(char *cmd, char **args, char **ae)
{
    int pid = fork();

    if (pid == 0) {
        errno = 0;
        execvp(cmd, args);
        switch (errno) {
        case ENOEXEC:
            dprintf(2, "%s: Exec format error. Binary file not executable.\n",
                cmd);
            break;
        case EPERM:
        case EACCES:
        case EISDIR:
            dprintf(2, "%s: Permission denied.\n", cmd);
            break;
        case ENOENT:
        default:
            dprintf(2, "%s: Command not found.\n", cmd);
            break;
        }
        exit(1);
    } else
        return show_signal(pid);
    return 1;
}

int launch_soft(parse_env_t *parse)
{
    char **env = getting_env(parse, 0);

    if (parse->cmd != NULL)
        return exec_arg(parse->cmd[0], parse->cmd, env);
    else
        show_tab_env(env);
    return 0;
}
