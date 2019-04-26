/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** magic
*/

#include "get_next_line.h"
#include "my.h"
#include "reports.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    Backquotes = 0,
    Parens = 1,
} CommandSubstType;

static OPTION(SizeT) find_paren(const char *line, size_t idx)
{
    bool quoted = false;

    for (size_t i = idx; line[i]; i++) {
        if (line[i] == '\\')
            i += !!(line[i + 1]);
        else if (quoted == false && line[i] == '\'') {
            i += 1;
            while (line[i] && line[i] != '\'')
                i += 1;
            i -= (line[i] == 0);
        } else if (line[i] == '"') {
            quoted = !quoted;
        } else if (quoted == false && line[i] == ')') {
            return SOME(SizeT, i - idx);
        }
    }
    report_unmatched_parenthesis(line, idx);
    return NONE(SizeT);
}

static OPTION(SizeT) find_quote(const char *line, size_t i)
{
    ssize_t idx = lstr_index_of(line, i, "`");
    if (idx == -1) {
        report_unmatched_quote(line, i);
        return NONE(SizeT);
    }
    return SOME(SizeT, idx - i);
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

static void exec_magic(Shell *shell, char *line, size_t i, size_t len,
    bool quoted, CommandSubstType type)
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
        if (asprintf(&ret, "%.*s%s%s", (int)(i), shell->line, subst,
                shell->line + i + len + 2 + type) == -1)
            return;
    } else {
        subst = sanitize(subst, true);
        if (asprintf(&ret, "%.*s%s%s", (int)(i), shell->line, subst,
                shell->line + i + len + 2 + type) == -1)
            return;
    }
    free(shell->line);
    shell->line = ret;
}

int magic(Shell *shell)
{
    bool quoted = false;

    for (ssize_t i = 0; shell->line[i]; i++) {
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
            OPTION(SizeT) opt_len = find_quote(shell->line, i + 1);
            if (IS_SOME(opt_len)) {
                size_t len = OPT_UNWRAP(opt_len);
                char *line = strndup(shell->line + i + 1, len);
                exec_magic(shell, line, i, len, quoted, Backquotes);
                i = -1;
            } else {
                return -1;
            }
        } else if (lstr_starts_with(shell->line + i, "$(")) {
            OPTION(SizeT) opt_len = find_paren(shell->line, i + 2);
            if (IS_SOME(opt_len)) {
                size_t len = OPT_UNWRAP(opt_len);
                char *line = strndup(shell->line + i + 2, len);
                exec_magic(shell, line, i, len, quoted, Parens);
                i = -1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}
