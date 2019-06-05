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

typedef struct {
    char *name;
    bool enclosed;
} Var;

DEF_OPTION(Var, Var);

// static char *get_arg(Shell *shell, int *cur)
// {
//     int nb = atoi(line + *cur + 1);
//     int len = 0;

//     while (line[*cur + 1 + len] && line[*cur + 1 + len] >= '0'
//     &&
//         line[*cur + 1 + len] <= '9')
//         len += 1;
//     return fmtstr("%.*s%s%s", *cur, line,
//         (shell->av && nb < nb_args(shell->av)) ? shell->av[nb] : "",
//         line + *cur + len + 1);
// }

static OPTION(Var) get_varname(char *str)
{
    size_t i = 0;
    char quotes[][2] = {
        {'{', '}'},
        {'[', ']'},
        {0, 0},
    };

    for (size_t q = 0; quotes[q][0] != 0; q += 1) {
        char open = quotes[q][0];
        char close = quotes[q][1];
        if (*str == open) {
            while (str[i + 1] && str[i + 1] != close)
                i += 1;
            if (str[i + 1] != 0 && i > 0) {
                Var ret = (Var){
                    .name = strndup(str + 1, i),
                    .enclosed = true,
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
        .enclosed = false,
    };
    return SOME(Var, ret);
}

// TODO: Re-implement shell args ($0 and ${0})
static OPTION(CharPtr)
    substitute_var(Shell *shell, char *line, long *cur, Var var, bool quoted)
{
    char *str = 0;
    char *resolved = 0;

    if (!strncmp(line + *cur, "$?", 2)) {
        str =
            fmtstr("%.*s%d%s", *cur, line, shell->exit_code, line + *cur + 2);
    } else if (!strncmp(line + *cur, "$$", 2)) {
        str = fmtstr("%.*s%d%s", *cur, line, getpid(), line + *cur + 2);
    } else if (strlen(var.name) == 0) {
        return SOME(CharPtr, line);
    } else if (
        // clang-format off
        (resolved = getenv(var.name)) ||
        (resolved = lhmap_get(shell->vars, var.name))
        // clang-format on
    ) {
        char *(*sanitize_func)(char *, bool) =
            quoted ? sanitize_double_quotes : sanitize;
        resolved = sanitize_func(resolved, false);
        str = fmtstr("%.*s%s%s", *cur, line, resolved,
            line + *cur + strlen(var.name) + (var.enclosed ? 3 : 1));
        free(resolved);
    } else {
        eputstr("%s: Undefined variable.\n", var.name);
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
            OPTION(Var) var = get_varname(line + cur + 1);
            if (IS_NONE(var))
                continue;
            OPTION(CharPtr)
            opt = substitute_var(shell, line, &cur, OPT_UNWRAP(var), quoted);
            if (IS_NONE(opt)) {
                return NONE(CharPtr);
            } else {
                line = OPT_UNWRAP(opt);
            }
        }
    }
    return SOME(CharPtr, line);
}
