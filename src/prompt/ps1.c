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

void ps1_prompt(shell_t *shell)
{
    char *ps1 = OPT_UNWRAP_OR(OPT_FROM_NULLABLE(CharPtr, getenv("PS1")), "");

    fflush(stdout);
    for (size_t i = 0; ps1[i]; i++) {
        if (ps1[i] == '\\') {
            switch (ps1[++i]) {
            case 0:
                i -= 1;
            case '\\':
                my_putchar('\\');
                break;
            case 'h':
            case 'H': {
                OPTION(CharPtr) hostname = get_hostname();
                OPT_AND_THEN(hostname, my_putstr);
                OPT_AND_THEN(hostname, free);
            } break;
            case 's':
                my_putstr("42sh");
                break;
            case 'w':
                OPT_AND_THEN(
                    OPT_FROM_NULLABLE(CharPtr, shell->current), my_putstr);
                break;
            case 'W': {
                OPTION(CharPtr)
                path = OPT_FROM_NULLABLE(CharPtr, shell->current);
                path = OPT_AND_THEN_NULLABLE(CharPtr, path, strdup);
                OPTION(CharPtr)
                name = OPT_AND_THEN_NULLABLE(CharPtr, path, basename);
                OPT_AND_THEN(name, my_putstr);
                OPT_AND_THEN(path, free);
            } break;
            case 'u': {
                OPTION(CharPtr)
                login = OPT_FROM_NULLABLE(CharPtr, getenv("LOGNAME"));
                OPT_AND_THEN(login, my_putstr);
            } break;
            case '$':
                my_putchar(getuid() ? '$' : '#');
                break;
            case '?':
                my_put_nbr(shell->exit_code);
                break;
            case 'n':
                my_putchar('\n');
                break;
            case 't':
                my_putchar('\t');
                break;
            case 'a':
                my_putchar('\a');
                break;
            case 'r':
                my_putchar('\r');
                break;
            case 'e':
                my_putchar('\e');
                break;
            case 'g': {
                OPTION(CharPtr)
                branch = OPT_FROM_NULLABLE(CharPtr, show_cur_branch());
                OPT_AND_THEN(branch, my_putstr);
                OPT_AND_THEN(branch, free);
            } break;
            case '[':
            case ']':
            default:
                break;
            }
        }
        else {
            my_putchar(ps1[i]);
        }
    }
    fflush(stdout);
}
