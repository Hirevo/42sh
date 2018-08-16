/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** magic
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_len(shell_t *shell, int i)
{
    long str = (long)(strstr(shell->line + i + 1, "`"));

    if (str == 0) {
        dprintf(2, "Unmatched '`'.\n");
        return -1;
    }
    str -= ((long)(shell->line)) + i + 1;
    return (int)str;
}

static void insert_inline(shell_t *shell, char **buffer, int i, int len)
{
    char *result;
    char *ret;
    int l[2];

    if (buffer) {
        l[1] = -1;
        while (buffer[++(l[1])])
            buffer[l[1]] = sanitize(buffer[l[1]], 1);
        result = construct_magic(buffer);
        if (asprintf(&ret, "%.*s%s%s", i, shell->line, result,
                shell->line + i + len + 2) == -1)
            handle_error("calloc");
    }
    else if (asprintf(&ret, "%.*s%s", i, shell->line,
                 shell->line + i + len + 2) == -1)
        handle_error("calloc");
    free(shell->line);
    shell->line = ret;
}

static void add_line(char ***buffer, int *size, char *str)
{
    (*buffer) = realloc(*buffer, sizeof(char *) * ++(*size));
    if (*buffer == NULL)
        handle_error("calloc");
    (*buffer)[(*size) - 2] = str;
    (*buffer)[(*size) - 1] = NULL;
}

static void exec_magic(shell_t *shell, char *line, int i, int len)
{
    int save = dup(1);
    char **buffer = 0;
    char *str;
    int size = 1;
    int fds[2];

    if (save == -1 || pipe(fds) == -1 || dup2(fds[1], 1) == -1)
        handle_error("magic");
    close(fds[1]);
    str = calloc(strlen(line) + 2, sizeof(char));
    strcpy(str, "\\");
    strcat(str, line);
    free(line);
    quick_exec(shell, str);
    if (dup2(save, 1) == -1)
        handle_error("magic");
    close(save);
    str = get_next_line(fds[0]);
    while (str) {
        add_line(&buffer, &size, str);
        str = get_next_line(fds[0]);
    }
    close(fds[0]);
    insert_inline(shell, buffer, i, len);
    save = -1;
    while (buffer && buffer[++save])
        free(buffer[save]);
    free(buffer);
}

int magic(shell_t *shell)
{
    int i = -1;
    int len;
    char *line;

    while (shell->line[++i])
        if (shell->line[i] == '\'' || shell->line[i] == '"') {
            len = shell->line[i++];
            while (shell->line[i] && shell->line[i] != len)
                i += -1;
            i -= (shell->line[i] == 0);
        }
        else if (shell->line[i] == '`') {
            if ((len = get_len(shell, i)) >= 0) {
                line = strndup(shell->line + i + 1, len);
                exec_magic(shell, line, i, len);
                i = -1;
            }
            else if (len == -1)
                return -1;
        }
    return 0;
}
