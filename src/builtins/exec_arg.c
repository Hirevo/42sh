/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec_arg
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int is_in_env(char *str, char c)
{
    int i;

    i = 0;
    while (str[i]) {
        if (str[i] == c)
            return 1;
        i += 1;
    }
    return 0;
}

void free_char_double(char **ch)
{
    int i;

    i = 0;
    while (ch && ch[i]) {
        free(ch[i]);
        i += 1;
    }
    free(ch);
}

static char **get_def_path(void)
{
    char **ret = calloc(3, sizeof(char *));

    if (ret == NULL)
        return NULL;
    ret[2] = NULL;
    ret[0] = strdup("/bin");
    ret[1] = strdup("/usr/bin");
    return ret;
}

int exec_path(char *cmd, char **arg, char **ae)
{
    int i;
    char **l_path;
    char *path;
    char *tmp;

    path = getenv("PATH");
    if (path != NULL)
        l_path = my_split_char(path, ':');
    else
        l_path = get_def_path();
    i = 0;
    while (l_path && l_path[i]) {
        if (l_path[i][strlen(l_path[i]) - 1] != '/')
            tmp = my_strcatdup(l_path[i], "/");
        else
            tmp = strdup(l_path[i]);
        if (print_error_path(my_strcatdup(tmp, cmd)))
            return 2;
        if (execve(my_strcatdup(tmp, cmd), arg, ae) != -1)
            return 1;
        i += 1;
    }
    free_char_double(l_path);
    return 0;
}

int exec_arg(char *cmd, char **arg, char **ae)
{
    int pid;
    int ret;

    pid = fork();
    if (pid == 0) {
        if (is_in_env(cmd, '/')) {
            exec_not_path(cmd, arg, ae);
            exit(1);
        }
        else {
            ret = exec_path(cmd, arg, ae);
            if (ret == 0)
                dprintf(2, "%s: Command not found.\n", cmd);
            exit(1);
        }
    }
    else
        return show_signal(pid);
    return 1;
}
