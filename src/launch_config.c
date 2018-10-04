/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** launch_config
*/

#include "get_next_line.h"
#include "my.h"
#include "server.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int launch_config(shell_t *shell)
{
    int ret;
    char *prompt;
    t_config config;

    if (!isatty(0)) {
        dprintf(2, "You can't launch the configuration.\n");
        return 1;
    }
    config.env = environ;
    config.prompt = shell->prompt;
    ret = config_http(shell, &config);
    shell->prompt = config.prompt;
    asprintf(&prompt, "%d", config.prompt);
    setenv("PROMPT", prompt, 1);
    free(prompt);
    return ret;
}
