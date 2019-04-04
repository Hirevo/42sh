/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *g_built_tab[] = {
    "alias",
    "cd",
    "config",
    "dualcast",
    "history",
    "echo",
    "exit",
    "setenv",
    "unalias",
    "unsetenv",
    "builtins",
    "prompt",
    "env",
    "set",
    "unset",
    "where",
    "which",
    "parserll",
    NULL,
};

static int show_builtins(shell_t *shell, int args)
{
    (void)(args);
    if (isatty(1)) {
        char *tmp1 = strdup("echo '");
        char *tmp2 = 0;
        if (tmp1 == 0)
            return 1;
        for (int i = 0; g_built_tab[i]; i++) {
            if (asprintf(&tmp2, "%s%s\n", tmp1, g_built_tab[i]) == -1)
                return 1;
            free(tmp1);
            tmp1 = tmp2;
        }
        if (asprintf(&tmp2, "%s' | sort | column", tmp1) == -1)
            return 1;
        free(tmp1);
        tmp1 = tmp2;
        quick_exec(shell, tmp1);
    } else {
        for (int i = 0; g_built_tab[i]; i++)
            printf("%s\n", g_built_tab[i]);
    }
    return 0;
}

static void init_fnt_builtin(
    int (*built_fnt[nb_built(g_built_tab)])(shell_t *, int))
{
    built_fnt[0] = &alias;
    built_fnt[1] = &cd_b;
    built_fnt[2] = &config_b;
    built_fnt[3] = &dualcast_b;
    built_fnt[4] = &disp_hist;
    built_fnt[5] = &echo_b;
    built_fnt[6] = &exit_b;
    built_fnt[7] = &setenv_b;
    built_fnt[8] = &unalias_b;
    built_fnt[9] = &unsetenv_b;
    built_fnt[10] = &show_builtins;
    built_fnt[11] = &prompt;
    built_fnt[12] = &env_b;
    built_fnt[13] = &set;
    built_fnt[14] = &unset;
    built_fnt[15] = &where;
    built_fnt[16] = &which;
    built_fnt[17] = &call_parser_ll;
}

char **get_builtin_tab(void)
{
    char **ret = calloc(nb_built(g_built_tab) + 1, sizeof(char *));

    if (ret == 0)
        return 0;
    for (int i = 0; g_built_tab[i]; i++)
        ret[i] = strdup(g_built_tab[i]);
    return ret;
}

int indexof_builtin(char *cmd)
{
    for (int i = 0; g_built_tab[i]; i++)
        if (strcmp(cmd, g_built_tab[i]) == 0)
            return i;
    return -1;
}

exec_status_t exec_builtins(shell_t *shell, int args)
{
    int (*built_fnt[nb_built(g_built_tab)])(shell_t *, int);
    int idx;

    init_fnt_builtin(built_fnt);
    idx = indexof_builtin(shell->cur->av[0]);
    if (idx >= 0 && idx < nb_built(g_built_tab)) {
        return (exec_status_t){
            .ok = true,
            .code = built_fnt[idx](shell, args),
        };
    } else {
        return (exec_status_t){
            .ok = false,
            .code = 1,
        };
    }
}
