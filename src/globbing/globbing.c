/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** globbing
*/

#include "get_next_line.h"
#include "my.h"
#include "option.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {
    EnclosureCurlyBrackets,
    EnclosureSquareBrackets,
} Enclosure;

DEF_OPTION(Enclosure, Enclosure);

typedef struct {
    char *name;
    OPTION(Enclosure) enclosure;
} Var;

DEF_OPTION(Var, Var);

typedef struct {
    char open;
    char close;
    OPTION(Enclosure) enclosure;
} EnclosureDefn;

static void *join_by_space(void *quoted, void *acc, void *elem, size_t idx)
{
    if (idx == 0)
        return acc;
    char *(*sanitize_func)(char *, bool) = quoted ? sanitize_double_quotes : sanitize;
    char *sanitized = sanitize_func(elem, false);
    if (!sanitized)
        return acc;
    if (idx - 1)
        acc = lstr_append(acc, " ");
    acc = lstr_append(acc, sanitized);
    free(sanitized);
    return acc;
}

static OPTION(Var) get_varname(char *str)
{
    size_t i = 0;
    EnclosureDefn quotes[] = {
        {'{', '}', SOME(Enclosure, EnclosureCurlyBrackets)},
        {'[', ']', SOME(Enclosure, EnclosureSquareBrackets)},
        {0, 0, NONE(Enclosure)},
    };

    for (size_t q = 0; quotes[q].open != 0; q += 1) {
        EnclosureDefn defn = quotes[q];
        if (*str == defn.open) {
            while (str[i + 1] && str[i + 1] != defn.close)
                i += 1;
            if (str[i + 1] != 0 && i > 0) {
                Var ret = (Var){
                    .name = strndup(str + 1, i),
                    .enclosure = defn.enclosure,
                };
                return SOME(Var, ret);
            } else
                return NONE(Var);
        }
    }
    while (str[i] && is_alphanum(str[i]))
        i += 1;
    Var ret = (Var){
        .name = strndup(str, i),
        .enclosure = NONE(Enclosure),
    };
    return SOME(Var, ret);
}

static OPTION(CharPtr) substitute_var(Shell *shell, char *line, long *cur, Var var, bool quoted)
{
    char *str = 0;
    char *resolved = 0;

    if (!strncmp(line + *cur, "$?", 2)) {
        str = fmtstr("%.*s%d%s", *cur, line, shell->exit_code, line + *cur + 2);
    } else if (!strncmp(line + *cur, "$$", 2)) {
        str = fmtstr("%.*s%d%s", *cur, line, getpid(), line + *cur + 2);
    } else if (!strncmp(line + *cur, "$#", 2)) {
        str = fmtstr("%.*s%d%s", *cur, line, labs((long)(lvec_size(shell->args)) - 1), line + *cur + 2);
    } else if (!strncmp(line + *cur, "$@", 2)) {
        char *rendered = lvec_reduce(shell->args, join_by_space, (void *)(quoted), strdup(""));
        if (rendered) {
            str = fmtstr("%.*s%s%s", *cur, line, rendered, line + *cur + 2);
        } else {
            str = fmtstr("%.*s%s", *cur, line, line + *cur + 2);
        }
    } else if (strlen(var.name) == 0) {
        return SOME(CharPtr, line);
    } else if (is_num(var.name)) {
        size_t pos = strtoul(var.name, NULL, 10);
        char *resolved = lvec_at(shell->args, pos);
        if (resolved) {
            char *(*sanitize_func)(char *, bool) = quoted ? sanitize_double_quotes : sanitize;
            resolved = sanitize_func(resolved, false);
            str = fmtstr("%.*s%s%s", *cur, line, resolved,
                line + *cur + strlen(var.name) + (IS_SOME(var.enclosure) ? 3 : 1));
            free(resolved);
        } else {
            str = fmtstr("%.*s%s", *cur, line,
                line + *cur + strlen(var.name) + (IS_SOME(var.enclosure) ? 3 : 1));
        }
    } else if (
        // clang-format off
        (resolved = getenv(var.name)) ||
        (resolved = lhmap_get(shell->vars, var.name))
        // clang-format on
    ) {
        char *(*sanitize_func)(char *, bool) = quoted ? sanitize_double_quotes : sanitize;
        resolved = sanitize_func(resolved, false);
        str = fmtstr("%.*s%s%s", *cur, line, resolved,
            line + *cur + strlen(var.name) + (IS_SOME(var.enclosure) ? 3 : 1));
        free(resolved);
    } else {
        eputstr("%s: undefined variable.\n", var.name);
        return NONE(CharPtr);
    }
    if (str == NULL)
        return NONE(CharPtr);
    *cur += (strlen(str) - strlen(line)) + 1;
    free(line);
    return SOME(CharPtr, str);
}

OPTION(CharPtr) substitute_vars(Shell *shell, char *line)
{
    bool quoted = false;

    for (long cur = 0; line[cur]; cur += 1) {
        if (line[cur] == '\\')
            cur += !!(line[cur + 1]);
        else if (line[cur] == '\'' && quoted == false) {
            cur += 1;
            while (line[cur] && line[cur] != '\'')
                cur += 1;
            cur -= (line[cur] == 0);
        } else if (line[cur] == '"')
            quoted = !quoted;
        else if (
            // clang-format off
            line[cur] == '$' &&
            line[cur + 1] &&
            line[cur + 1] != '"' &&
            !is_separator(line[cur + 1])
            // clang-format on
        ) {
            OPTION(Var) opt_var = get_varname(line + cur + 1);
            if (IS_NONE(opt_var))
                continue;
            Var var = OPT_UNWRAP(opt_var);
            OPTION(CharPtr) opt = substitute_var(shell, line, &cur, var, quoted);
            free(var.name);
            if (IS_NONE(opt)) {
                return NONE(CharPtr);
            } else {
                line = OPT_UNWRAP(opt);
            }
        }
    }
    return SOME(CharPtr, line);
}
