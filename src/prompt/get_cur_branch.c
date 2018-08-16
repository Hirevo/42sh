/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_cur_branch
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static char *cut_path(char *tmp)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *res;

    while (tmp && tmp[i] && j != 2) {
        if (tmp && tmp[i] == '/')
            j++;
        i++;
    }
    if (j != 2)
        return NULL;
    res = calloc(strlen(tmp) - i + 1, sizeof(char));
    if (res == NULL)
        return NULL;
    while (tmp[i])
        res[k++] = tmp[i++];
    res[k] = '\0';
    free(tmp);
    return res;
}

static int is_sha1(char *str)
{
    int i = 0;

    while (str[i]) {
        if (!((str[i] >= '0' && str[i] <= '9') ||
                (str[i] >= 'a' && str[i] <= 'f')))
            return 0;
        i += 1;
    }
    if (i != 40)
        return 0;
    return 1;
}

static char *find_branch(char *path)
{
    int fd = open(path, O_RDONLY);
    char *tmp;

    if (fd == -1)
        return NULL;
    tmp = get_next_line(fd);
    if (tmp == NULL) {
        close(fd);
        return NULL;
    }
    close(fd);
    if (is_sha1(tmp))
        return my_strndup(tmp, 7);
    return cut_path(tmp);
}

static int is_root(char *path)
{
    char *str;
    char *tmp = strdup(path);
    char *dir;
    int i;

    if (tmp == NULL)
        handle_error("calloc");
    dir = dirname(tmp);
    str = calloc(strlen(dir) + strlen("/home") + 1, sizeof(char));
    if (str == NULL)
        handle_error("calloc");
    strcat(strcpy(str, dir), "/home");
    i = access(str, F_OK);
    free(str);
    free(tmp);
    return (i == 0) ? 1 : 0;
}

char *show_cur_branch()
{
    char *branch;
    char *path = strdup("./.git");

    while (path != NULL)
        if (access(path, F_OK) == -1)
            if (is_root(path)) {
                free(path);
                path = NULL;
            }
            else
                path = my_fstrcat("../", path, 3);
        else {
            path = my_fstrcat(path, "/HEAD", 1);
            branch = find_branch(path);
            if (branch == NULL) {
                free(path);
                return NULL;
            }
            free(path);
            return branch;
        }
    return NULL;
}
