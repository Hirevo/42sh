/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** path
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int is_path(char *str)
{
    int i;

    i = -1;
    while (str[++i] != 0)
        if (str[i] == '/')
            return 1;
    return 0;
}

char **init_path(char *str)
{
    char **path;

    if (str == NULL)
        return NULL;
    path = my_split(str, ":");
    if (path == NULL)
        handle_error("calloc");
    return path;
}

void set_path(Shell *shell, char *path)
{
    int i = -1;
    int obj = my_strlen_spe(path, '=');
    char *name = calloc(obj + 1, sizeof(char));
    char *entry;

    (void)(shell);
    if (name == NULL)
        handle_error("calloc");
    while (++i < obj)
        name[i] = path[i];
    name[i] = 0;
    i = obj + 1;
    obj = my_strlen_spe(path + i, '\0');
    entry = calloc(obj + 1, sizeof(char));
    if (entry == NULL)
        handle_error("calloc");
    obj = i;
    i = -1;
    while ((path + obj)[++i] != 0)
        entry[i] = (path + obj)[i];
    entry[i] = 0;
    setenv(name, entry, 1);
    free(name);
    free(entry);
}

void parse_rc(Shell *shell)
{
    char *home = getenv("HOME");
    if (home == NULL)
        return;
    char *path = path_join(home, RC_FILE);
    if (path == NULL)
        return;
    int fd = open(path, O_RDONLY);
    free(path);
    if (fd == -1)
        return;
    for (char *line = get_next_line(fd); line; line = get_next_line(fd)) {
        if (is_valid_path(line))
            set_path(shell, line);
        free(line);
    }
    close(fd);
}
