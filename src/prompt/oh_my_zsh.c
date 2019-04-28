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

void oh_my_zsh(Shell *shell)
{
    char *git;

    fflush(stdout);
    if (shell->exit_code == 0)
        writestr("\e[32;1m");
    else
        writestr("\e[31;1m");
    writestr("→  ");
    writestr("\e[0m");
    char *cwd = getcwd(0, 0);
    if (cwd) {
        writestr("\e[36;1m");
        writestr(basename(cwd));
        writestr("\e[0m ");
        free(cwd);
    } else {
        writestr("\e[36;1m?\e[0m ");
    }
    git = show_cur_branch();
    if (git) {
        writestr("\e[34;1mgit:(\e[0m\e[31;1m");
        writestr(git);
        writestr("\e[0m\e[34;1m)\e[0m ");
        free(git);
    }
}
