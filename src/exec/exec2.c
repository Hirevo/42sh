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

void quick_exec(Shell *shell, char *str)
{
    char *save = shell->line;
    vec_t *fragments = shell->fragments;
    Command *cmds = shell->commands;

    if (is_line_empty(str))
        return;
    shell->commands = NULL;
    shell->fragments = NULL;
    shell->line = str;
    exec_line(shell, 0);
    shell->line = save;
    shell->fragments = fragments;
    shell->commands = cmds;
}
