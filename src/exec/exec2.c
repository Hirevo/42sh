/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exec2
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int compare_stats(struct stat *stats)
{
    if (stats->st_mode & S_IXUSR) {
        if (!S_ISDIR(stats->st_mode)) {
            return 0;
        } else {
            return -3;
        }
    } else {
        return -2;
    }
}

void quick_exec(Shell *shell, char *str)
{
    if (is_line_empty(str)) {
        free(str);
        return;
    }
    exec_line(shell, str, false);
}

OPTION(CharPtr) quick_exec_captured(Shell *shell, char *str)
{
    char name[] = "/tmp/42sh-capture-XXXXXX";
    int save = dup(1);
    int fd = ((save != -1) ? mkstemp(name) : -1);

    fflush(stdout);
    if (save == -1 || fd == -1 || dup2(fd, 1) == -1)
        return NONE(CharPtr);
    close(fd);

    quick_exec(shell, str);
    fflush(stdout);

    if (dup2(save, 1) == -1)
        return NONE(CharPtr);
    close(save);

    fd = open(name, O_RDONLY);
    if (fd == -1)
        return NONE(CharPtr);
    char *subst = read_all(fd);
    close(fd);
    remove(name);
    if (subst == 0)
        return NONE(CharPtr);
    return SOME(CharPtr, subst);
}