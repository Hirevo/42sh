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
        return strndup(tmp, 7);
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

static char *handle_standard(char *git_dir)
{
    char *path = my_fstrcat(git_dir, "/HEAD", FREE_LEFT);
    char *branch = find_branch(path);
    if (branch == NULL) {
        free(path);
        return NULL;
    }
    free(path);
    return branch;
}

static char *handle_submodule(char *path)
{
    int fd = open(path, O_RDONLY);

    free(path);
    if (fd == -1)
        return NULL;
    char *tmp = get_next_line(fd);
    close(fd);
    if (tmp == NULL || lstr_starts_with(tmp, "gitdir:") == false) {
        free(tmp);
        return NULL;
    } else {
        char *git_dir = tmp + 7;
        size_t count = 0;
        while (is_space(git_dir[count]))
            count += 1;
        git_dir = strdup(git_dir + count);
        free(tmp);
        if (git_dir == NULL)
            return NULL;
        return handle_standard(git_dir);
    }
    return NULL;
}

char *show_cur_branch(void)
{
    char *result = 0;
    char *path = strdup(".git");
    struct stat stats = {0};

    while (path != NULL) {
        if (stat(path, &stats) == -1 ||
            (S_ISREG(stats.st_mode) && !(result = handle_submodule(path))) ||
            (S_ISDIR(stats.st_mode) && !(result = handle_standard(path)))) {
            if (is_root(path)) {
                free(path);
                return NULL;
            } else
                path = my_fstrcat("../", path, FREE_RIGHT);
        } else {
            return result;
        }
    }
    return NULL;
}
