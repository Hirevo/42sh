/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** sauv
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char **add_to_cdouble(char *str, char **list)
{
    int i = 0;
    char **ret = calloc(nb_args(list) + 2, sizeof(char *));

    if (ret == NULL)
        return NULL;
    ret[nb_args(list) + 1] = NULL;
    while (list && list[i]) {
        ret[i] = strdup(list[i]);
        free(list[i]);
        i += 1;
    }
    ret[i] = strdup(str);
    free(list);
    return ret;
}

static void update_prompt(char ***file, shell_t *shell)
{
    int stop = 0;
    char *add;
    int i = 0;

    if (asprintf(&add, "PROMPT=%d", shell->prompt) == -1)
        handle_error("calloc");
    while ((*file)[i]) {
        if (!strncmp("PROMPT=", (*file)[i], 7)) {
            free((*file)[i]);
            (*file)[i] = strdup(add);
            stop = 1;
        }
        i += 1;
    }
    if (!stop)
        (*file) = add_to_cdouble(add, *file);
    free(add);
}

static void write_file(char **env)
{
    int i = 0;
    int fd;
    char *path = my_strcatdup(get_env("HOME"), "/");
    char *str;

    if (path == NULL)
        return;
    str = my_strcatdup(path, RC_FILE);
    fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1)
        return;
    free(path);
    free(str);
    i = 0;
    while (env[i]) {
        dprintf(fd, "%s\n", env[i]);
        i += 1;
    }
    free_tab(env);
    close(fd);
}

void sauv_prompt(shell_t *shell)
{
    char *home = get_env("HOME");
    char *path = home ?  my_strcatdup(home, "/") : 0;
    char *str = path ? my_strcatdup(path, RC_FILE) : 0;
    int fd = str ? open(str, O_RDONLY) : -1;

    if (fd == -1)
        return;
    free(path);
    free(str);
    char **file = load_file(fd);
    if (file == NULL) {
        close(fd);
        return;
    }
    close(fd);
    update_prompt(&file, shell);
    write_file(file);
}
