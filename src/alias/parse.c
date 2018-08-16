/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parse
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int is_valid_alias(char *path)
{
    int i = 0;

    if (path[i++] != 'a' || path[i++] != 'l' || path[i++] != 'i' ||
        path[i++] != 'a' || path[i++] != 's' || path[i++] != ' ')
        return 0;
    while (path[i] != '=')
        if (path[i++] == 0)
            return 0;
    if (path[++i] != '\'')
        return 0;
    while (path[++i] != '\'')
        if (path[i] == 0)
            return 0;
    if (path[++i] == 0)
        return 1;
    return 0;
}

void write_alias(int *fd, char *name, char *command)
{
    dprintf(*fd, "alias %s='%s'\n", name, command);
}

void save_alias(shell_t *shell)
{
    int fd;
    char *path = calloc(512, sizeof(char));

    if (shell->tty == 0 || shell->home == NULL || path == NULL)
        return;
    path[0] = 0;
    path = strcat(path, shell->home);
    if (shell->home[strlen(shell->home)] != '/')
        path[strlen(shell->home)] = '/';
    path[strlen(shell->home) + 1] = 0;
    path = strcat(path, ALIAS_FILE);
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return;
    lhmap_for_each(
        shell->alias, (void (*)(void *, char *, void *))(write_alias), &fd);
    free(path);
    close(fd);
}

void set_alias(shell_t *shell, char *path)
{
    alias_t alias;
    int i = -1;
    int obj = my_strlen_spe(path + 6, '=');

    alias.alias = calloc(obj + 1, sizeof(char));
    if (alias.alias == NULL)
        return;
    while (++i < obj)
        alias.alias[i] = (path + 6)[i];
    alias.alias[i] = 0;
    i = obj + 7;
    obj = my_strlen_spe(path + i + 1, '\'');
    alias.command = calloc(obj + 1, sizeof(char));
    if (alias.command == NULL)
        return;
    obj = i;
    i = -1;
    while ((path + obj + 1)[++i] != '\'')
        alias.command[i] = (path + obj + 1)[i];
    alias.command[i] = 0;
    add_alias(shell, alias.alias, alias.command);
    free(alias.alias);
    free(alias.command);
}

void init_aliases(shell_t *shell)
{
    int fd;
    char *path = calloc(512, sizeof(char));

    shell->alias = lhmap_new();
    if (shell->alias == NULL || shell->home == NULL || path == NULL)
        return;
    path[0] = 0;
    path = strcat(path, shell->home);
    if (shell->home[strlen(shell->home)] != '/')
        path[strlen(shell->home)] = '/';
    path[strlen(shell->home) + 1] = 0;
    path = strcat(path, ALIAS_FILE);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    free(path);
    path = get_next_line(fd);
    while (path) {
        if (is_valid_alias(path))
            set_alias(shell, path);
        free(path);
        path = get_next_line(fd);
    }
    close(fd);
}
