/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** magic
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <fcntl.h>
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

static char *read_all(int fd)
{
    char buffer[1024] = {0};
    char *ret = strdup("");
    ssize_t nb_bytes = 0;

    while ((nb_bytes = read(fd, buffer, 1023)) > 0) {
        buffer[nb_bytes] = 0;
        char *tmp = 0;
        if (asprintf(&tmp, "%s%s", ret, buffer) == -1) {
            free(ret);
            return 0;
        }
        free(ret);
        ret = tmp;
    }
    return ret;
}

static void exec_magic(shell_t *shell, char *line, int i, int len, bool quoted)
{
    char name[] = "/tmp/42sh-magic-XXXXXX";
    int save = dup(1);
    int fd = ((save != -1) ? mkostemp(name, O_CLOEXEC | O_RDONLY) : -1);

    if (save == -1 || fd == -1 || dup2(fd, 1) == -1)
        handle_error("magic");
    char *str = strdup(line);
    quick_exec(shell, str);
    if (dup2(save, 1) == -1)
        handle_error("magic");
    close(save);
    lseek(fd, SEEK_SET, 0);
    char *subst = read_all(fd);
    close(fd);
    if (subst == 0)
        return;
    char *ret = 0;
    if (quoted) {
        subst = sanitize_double_quotes(subst, true);
        if (asprintf(&ret, "%.*s%s%s", i, shell->line, subst,
                shell->line + i + len + 2) == -1)
            return;
    } else {
        subst = sanitize(subst, true);
        if (asprintf(&ret, "%.*s%s%s", i, shell->line, subst,
                shell->line + i + len + 2) == -1)
            return;
    }
    free(shell->line);
    shell->line = ret;
}

int magic(shell_t *shell)
{
    int i = -1;
    int len;
    char *line;
    bool quoted = false;

    while (shell->line[++i])
        if (shell->line[i] == '\\')
            i += !!(shell->line[i + 1]);
        else if (shell->line[i] == '\'') {
            i += 1;
            while (shell->line[i] && shell->line[i] != '\'')
                i += 1;
            i -= (shell->line[i] == 0);
        } else if (shell->line[i] == '"') {
            quoted = !quoted;
        } else if (shell->line[i] == '`') {
            if ((len = get_len(shell, i)) >= 0) {
                line = strndup(shell->line + i + 1, len);
                exec_magic(shell, line, i, len, quoted);
                i = -1;
            } else if (len == -1)
                return -1;
        }
    return 0;
}
