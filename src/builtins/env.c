/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"

void show_tab_env(char **env)
{
    int i;

    i = 0;
    while (env && env[i]) {
        printf("%s\n", env[i]);
        i += 1;
    }
}

void show_env(void)
{
    int i;

    i = 0;
    while (environ && environ[i]) {
        printf("%s\n", environ[i]);
        i += 1;
    }
}

int env_b(shell_t *shell, int args)
{
    parse_env_t *parse;

    if (args == 1)
        show_env();
    else {
        if ((parse = parse_env(shell->cur->av)) == NULL) {
            dprintf(2, "env: parse error.\n");
            return 1;
        }
        if (parse->null == 1 && parse->cmd != NULL)
            dprintf(2,
                "env: cannot specify --null (-0) with "
                "command.\n");
        else if (parse->null == 1 && parse->cmd == NULL)
            show_env_parse(parse);
        else
            return launch_soft(parse);
    }
    return 0;
}
