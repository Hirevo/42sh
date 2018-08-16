/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** check_file
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int print_error(char *cmd)
{
    struct stat stats;

    if (stat(cmd, &stats) == -1)
        return dprintf(2, "%s: Command not found.\n", cmd), 0;
    else if ((stats.st_mode & S_IXUSR) == 0)
        return dprintf(2, "%s: Permission denied.\n", cmd), 0;
    else if (S_ISDIR(stats.st_mode))
        return dprintf(2, "%s: Permission denied.\n", cmd), 0;
    return 1;
}

int print_error_path(char *cmd)
{
    struct stat stats;

    if (stat(cmd, &stats) == -1)
        return 0;
    if (S_ISDIR(stats.st_mode) || (stats.st_mode & S_IXUSR) == 0)
        return dprintf(2, "%s: Permission denied.\n", cmd), 1;
    return 0;
}

int check_access_env(char *cmd)
{
    struct stat stats;

    if (stat(cmd, &stats) == -1)
        dprintf(2, "%s: No such file or directory.\n", cmd);
    else if (!S_ISDIR(stats.st_mode))
        dprintf(2, "%s: Not a directory.\n", cmd);
    else if ((stats.st_mode & S_IXUSR) == 0)
        dprintf(2, "%s: Permission denied.\n", cmd);
    return 1;
    if (!isatty(0))
        exit(1);
    return 1;
}
