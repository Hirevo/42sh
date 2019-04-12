/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** mysh_arrow
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void mysh_arrow(shell_t *shell)
{
    OPTION(CharPtr) git = OPT_FROM_NULLABLE(CharPtr, show_cur_branch());

    fflush(stdout);
    if (shell->exit_str)
        printf("\e[1m\e[38;2;255;255;85m(%s)\e[0m ", shell->exit_str);
    printf("\e[1m\e[38;2;255;85;85m42sh\e[21m\e[0m \e[1m\e[38;2;38;252;166m");
    if (shell->current != NULL)
        printf("%s", shell->current);
    printf("\e[0m \e[1m");
    if (IS_SOME(git))
        printf("\e[1m[\e[38;2;0;133;255m%s\e[0m\e[1m] ", OPT_UNWRAP(git));
    OPT_AND_THEN(git, free);
    printf(getuid() ? "=> " : "#> ");
    fflush(stdout);
}
