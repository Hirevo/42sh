/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** oh_my_zsh
*/

#include "my.h"
#include "shell.h"
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

void oh_my_zsh(shell_t *shell)
{
    char *git;

    fflush(stdout);
    if (shell->exit_code == 0)
        printf("%s", "\e[32;1m");
    else
        printf("%s", "\e[31;1m");
    printf("%s", "→  ");
    printf("%s", "\e[0m");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        printf("\e[36;1m%s\e[0m ", basename(cwd));
        free(cwd);
    } else {
        printf("\e[36;1m?\e[0m ");
    }
    git = show_cur_branch();
    if (git) {
        printf(
            "\e[34;1mgit:(\e[0m\e[31;1m%s\e[0m\e[34;1m)\e[0m ",
            git
        );
        free(git);
    }
    fflush(stdout);
}
