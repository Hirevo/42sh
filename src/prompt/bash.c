/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** bash
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bash_prompt(shell_t *shell)
{
    OPTION(CharPtr) login = OPT_FROM_NULLABLE(CharPtr, getenv("LOGNAME"));
    OPTION(CharPtr) hostname = get_hostname();

    (void)(shell);
    fflush(stdout);
    printf("\e[32;1m%s@%s\e[0m", OPT_UNWRAP_OR(login, "???"),
        OPT_UNWRAP_OR(hostname, "???"));
    OPT_AND_THEN(hostname, free);
    printf("%s", ":");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        char *path = pretty_path(cwd);
        free(cwd);
        if (path) {
            printf("\e[34;1m%s\e[0m", path);
            free(path);
        } else {
            printf("\e[34;1m%s\e[0m", cwd);
        }
    } else {
        printf("\e[34;1m?\e[0m");
    }
    printf("%s", getuid() ? "$ " : "# ");
    fflush(stdout);
}
