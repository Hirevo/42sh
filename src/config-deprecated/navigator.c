/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** navigator
*/

#include "my.h"
#include "server.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static char **get_path(char **ae)
{
    char *tmp = get_env("PATH");
    char **ret = calloc(3, sizeof(char *));

    (void)(ae);
    if (tmp != NULL)
        return my_split(tmp, ":");
    if (ret == NULL)
        return NULL;
    ret[0] = strdup("/bin");
    ret[1] = strdup("/usr/bin");
    return ret;
}

static char *test_access(char *tmp)
{
    char *ret = path_join(tmp, CHROME);

    if (access(ret, X_OK) == 0) {
        free(tmp);
        return ret;
    }
    free(ret);
    ret = path_join(tmp, FIREFOX);
    if (access(ret, X_OK) == 0) {
        free(tmp);
        return ret;
    }
    free(ret);
    return NULL;
}

char *find_navigator(char **ae)
{
    char *ret;
    char **path = get_path(ae);
    int i = 0;

    if (path == NULL)
        return NULL;
    while (path[i]) {
        ret = test_access(path[i]);
        if (ret != NULL) {
            free_tab(path);
            return ret;
        }
        i += 1;
    }
    free_tab(path);
    return NULL;
}

static int dup_child(void)
{
    int fd = open("/dev/null", O_RDONLY);

    if (fd == -1)
        return 1;
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    return 0;
}

int launch_nav(char *path, int port, char **ae)
{
    int pid;
    char **argv = calloc(3, sizeof(char *));

    if (argv == NULL)
        return 1;
    argv[0] = path;
    argv[1] = strdup(PATH_WEB);
    argv[1] = my_fstrcat(argv[1], int_toc(port), 2);
    pid = fork();
    if (pid == 0) {
        dup_child();
        execve(path, argv, ae);
        free_tab(argv);
        exit(0);
    }
    free_tab(argv);
    return 0;
}
