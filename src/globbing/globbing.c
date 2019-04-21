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

static int get_arg(Shell *shell, char **str, int *cur)
{
    int nb = atoi(shell->line + *cur + 1);
    int len = 0;

    while (shell->line[*cur + 1 + len] && shell->line[*cur + 1 + len] >= '0' &&
        shell->line[*cur + 1 + len] <= '9')
        len += 1;
    return asprintf(str, "%.*s%s%s", *cur, shell->line,
        (shell->av && nb < nb_args(shell->av)) ? shell->av[nb] : "",
        shell->line + *cur + len + 1);
}

static OPTION(Var) get_gvar(char *str)
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

static void final_checks(Shell *shell, char *str, int *cur, int i)
{
    if (i == -1 || str == NULL)
        handle_error("calloc");
    *cur += (strlen(str) - strlen(shell->line)) + 1;
    free(shell->line);
    shell->line = str;
}

static bool replace_var(Shell *shell, int *cur, Var var, bool is_free)
{
    char *str;
    char *resolved;
    int ret = 0;

    if (!strncmp(shell->line + *cur, "$?", 2))
        ret = asprintf(&str, "%.*s%d%s", *cur, shell->line, shell->exit_code,
            shell->line + *cur + 2);
    else if (!strncmp(shell->line + *cur, "$$", 2))
        ret = asprintf(&str, "%.*s%d%s", *cur, shell->line, getpid(),
            shell->line + *cur + 2);
    else if (strlen(var.name) == 0) {
        return true;
    } else if ((resolved = lhmap_get(shell->vars, var.name)) ||
        (resolved = getenv(var.name))) {
        char *(*sanitize_func)(char *, bool) =
            is_free ? sanitize_single_arg : sanitize_double_quotes;
        resolved = sanitize_func(resolved, false);
        ret = asprintf(&str, "%.*s%s%s", *cur, shell->line, resolved,
            shell->line + *cur + strlen(var.name) + (var.enclosed ? 3 : 1));
        free(resolved);
    } else if (shell->line[*cur + 1] >= '0' && shell->line[*cur + 1] <= '9')
        ret = get_arg(shell, &str, cur);
    else {
        dprintf(2, "%s: Undefined variable.\n", var.name);
        return false;
    }
    final_checks(shell, str, cur, ret);
    return true;
}

int parse_vars(Shell *shell)
{
    bool is_free = true;

    for (int cur = 0; shell->line[cur]; cur += 1) {
        if (shell->line[cur] == '\\')
            cur += !!(shell->line[cur + 1]);
        else if (shell->line[cur] == '\'' && is_free) {
            cur += 1;
            while (shell->line[cur] && shell->line[cur] != '\'')
                cur += 1;
        } else if (shell->line[cur] == '"')
            is_free = !is_free;
        else if (shell->line[cur] == '$' && shell->line[cur + 1] &&
            !is_separator(shell->line[cur + 1]) &&
            shell->line[cur + 1] != '"') {
            OPTION(Var) var = get_gvar(shell->line + cur + 1);
            if (IS_NONE(var))
                continue;
            if (replace_var(shell, &cur, OPT_UNWRAP(var), is_free) == false)
                return -1;
        }
    }
    return 0;
}
