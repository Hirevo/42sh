/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** check_file_2
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int is_folder(char *path)
{
    struct stat stats;

    if (stat(path, &stats) == -1)
        return 0;
    else if (S_ISDIR(stats.st_mode))
        return 1;
    return 0;
}
