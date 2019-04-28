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

static void update_prompt(char ***file, Shell *shell)
{
    int stop = 0;
    char *add = fmtstr("PROMPT=%d", shell->prompt);
    int i = 0;

    if (add == 0)
        handle_error("calloc");
    while ((*file)[i]) {
        if (lstr_starts_with((*file)[i], "PROMPT=")) {
            free((*file)[i]);
            (*file)[i] = strdup(add);
            stop = 1;
            break;
        }
        i += 1;
    }
    if (!stop)
        (*file) = add_to_cdouble(add, *file);
    free(add);
}

static void write_file(char **env)
{
    char *home = getenv("HOME");
    char *path = home ? path_join(home, RC_FILE) : 0;

    if (path == NULL)
        return;
    int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1)
        return;
    free(path);
    for (size_t i = 0; env[i]; i++)
        dputstr(fd, "%s\n", env[i]);
    free_tab(env);
    close(fd);
}

void sauv_prompt(Shell *shell)
{
    char *home = getenv("HOME");
    char *path = home ? path_join(home, RC_FILE) : 0;
    int fd = path ? open(path, O_RDONLY) : -1;

    if (fd == -1)
        return;
    free(path);
    char **file = load_file(fd);
    if (file == NULL) {
        close(fd);
        return;
    }
    close(fd);
    update_prompt(&file, shell);
    write_file(file);
}
