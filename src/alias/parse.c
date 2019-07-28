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

bool is_valid_alias(char *path)
{
    size_t i = 6;

    if (lstr_starts_with(path, "alias ") == false)
        return false;
    while (path[i] != '=')
        if (path[i++] == 0)
            return false;
    if (path[++i] != '\'')
        return false;
    while (path[++i] != '\'')
        if (path[i] == 0)
            return false;
    if (path[++i] == 0)
        return true;
    return false;
}

void write_alias(int *fd, char *name, char *command)
{
    dprintf(*fd, "alias %s='%s'\n", name, command);
}

void save_alias(Shell *shell)
{
    char *home = getenv("HOME");

    if (shell->tty == 0 || home == 0)
        return;
    char *path = path_join(home, ALIAS_FILE);
    if (path == 0)
        return;
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(path);
    if (fd == -1)
        return;
    lhmap_for_each(
        shell->aliases, (void (*)(void *, char *, void *))(write_alias), &fd);
    close(fd);
}

void set_alias(Shell *shell, char *path)
{
    size_t obj = strcspn(path + 6, "=");
    size_t idx = 0;

    char *alias_name = calloc(obj + 1, sizeof(char));
    if (alias_name == NULL)
        return;
    for (idx = 0; idx < obj; idx++) {
        alias_name[idx] = (path + 6)[idx];
    }
    alias_name[idx] = 0;
    idx = obj + 7;
    obj = strcspn(path + idx + 1, "'");
    char *alias_command = calloc(obj + 1, sizeof(char));
    if (alias_command == NULL)
        return;
    obj = idx;
    for (idx = 0; (path + obj + 1)[idx] != '\''; idx++) {
        alias_command[idx] = (path + obj + 1)[idx];
    }
    alias_command[idx] = 0;
    add_alias(shell, alias_name, alias_command);
    free(alias_name);
    free(alias_command);
}

void init_aliases(Shell *shell)
{
    char *home = getenv("HOME");

    shell->aliases = lhmap_new();
    if (shell->aliases == NULL)
        return;
    char *path = path_join(home, ALIAS_FILE);
    if (path == 0)
        return;
    int fd = open(path, O_RDONLY);
    free(path);
    if (fd == -1)
        return;
    for (char *line = get_next_line(fd); line; line = get_next_line(fd)) {
        if (is_valid_alias(line))
            set_alias(shell, line);
        free(line);
    }
    close(fd);
}
