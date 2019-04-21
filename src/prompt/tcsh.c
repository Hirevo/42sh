/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** tcsh
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void tcsh_prompt(Shell *shell)
{
    OPTION(CharPtr) hostname = get_hostname();

    (void)(shell);
    fflush(stdout);
    printf("\e[4m%s\e[0m", OPT_UNWRAP_OR(hostname, "???"));
    OPT_AND_THEN(hostname, free);
    printf("%s", ":");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        char *path = pretty_path(cwd);
        free(cwd);
        if (path) {
            printf("\e[1m%s\e[0m", path);
            free(path);
        } else {
            printf("\e[1m%s\e[0m", cwd);
        }
    } else {
        printf("\e[1m?\e[0m");
    }
    printf("%s", "> ");
    fflush(stdout);
}
