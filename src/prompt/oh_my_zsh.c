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
        printf("%s", "\033[32;1m");
    else
        printf("%s", "\033[31;1m");
    printf("%s", "→  ");
    printf("%s", "\033[0m");
    printf("\033[36;1m%s\033[0m ", basename(shell->current));
    git = show_cur_branch();
    if (git) {
        printf("\033[34;1mgit:(\033[0m\033[31;1m\
%s\033[0m\033[34;1m)\033[0m ",
            git);
        free(git);
    }
    fflush(stdout);
}
