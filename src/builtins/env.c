/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** env
*/

#include "builtin.h"
#include "my.h"
#include "shell.h"

int env_b(shell_t *shell, vec_t *args)
{
    (void)(shell);
    if (lvec_size(args) == 1) {
        for (size_t i = 0; environ && environ[i]; i++)
            putstr("%s\n", environ[i]);
    } else {
        eputstr("env: too many arguments.\n");
        // parse_env_t *parse = parse_env(args);
        // if (parse == NULL) {
        //     eputstr("env: parse error.\n");
        //     return 1;
        // }
        // if (parse->null == 1 && parse->cmd != NULL)
        //     eputstr("env: cannot specify --null (-0) with command.\n");
        // else if (parse->null == 1 && parse->cmd == NULL)
        //     show_env_parse(parse);
        // else
        //     return launch_soft(parse);
    }
    return 0;
}
