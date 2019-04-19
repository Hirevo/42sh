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

exec_status_t exec_redirected_builtins(shell_t *shell, int fds[2])
{
    int fd;
    int last;
    command_t *head;
    exec_status_t ret;

    head = shell->cur;
    if (lhmap_get(shell->builtins, lvec_front(head->av)) == 0)
        return (exec_status_t){
            .ok = false,
            .code = 1,
        };
    fd = 0;
    if (head->r_type) {
        last = dup(1);
        fd = setup_right_redirect(head, fds, (head->r_type[1] == 0));
    }
    ret = exec_builtins(shell, head->av);
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
