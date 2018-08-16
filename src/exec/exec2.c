/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec2
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int compare_stats(struct stat *stats)
{
    if (stats->st_mode & S_IXUSR)
        if (!S_ISDIR(stats->st_mode))
            return 0;
        else
            return -3;
    else
        return -2;
}

unsigned int exec_redirected_builtins(
    shell_t *shell, int count, int *i, int fds[2])
{
    int fd;
    int last;
    command_t *head;
    unsigned int ret;

    head = shell->cur;
    if (indexof_builtin(head->av[0]) == -1)
        return 0;
    fd = 0;
    if (head->r_type) {
        last = dup(1);
        fd = setup_right_redirect(head, fds, (head->r_type[1] == 0));
    }
    ret = exec_builtins(shell, count, i);
    if (fd) {
        close(fd);
        dup2(last, 1);
        close(last);
    }
    return ret;
}

void quick_exec(shell_t *shell, char *str)
{
    char *save = shell->line;
    char **final = shell->final;
    command_t *cmds = shell->commands;

    if (is_line_empty(str))
        return;
    shell->commands = NULL;
    shell->final = NULL;
    shell->line = str;
    exec_line(shell, 0);
    shell->line = save;
    shell->final = final;
    shell->commands = cmds;
}
