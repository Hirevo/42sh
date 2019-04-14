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
            case 'h': {
                OPTION(CharPtr) hostname = get_hostname();
                if (IS_SOME(hostname)) {
                    char *hostname_u = OPT_UNWRAP(hostname);
                    ssize_t idx = lstr_index_of(hostname_u, 0, ".");
                    if (idx == -1)
                        my_putstr(hostname_u);
                    else
                        write(1, hostname_u, idx);
                    free(hostname_u);
                }
            } break;
            case 'H': {
                OPTION(CharPtr) hostname = get_hostname();
                OPT_AND_THEN(hostname, my_putstr);
                OPT_AND_THEN(hostname, free);
            } break;
            case 's':
                my_putstr("42sh");
                break;
            case 'w': {
                OPTION(CharPtr) cwd = OPT_FROM_NULLABLE(CharPtr, getcwd(0, 0));
                if (IS_SOME(cwd)) {
                    char *ucwd = OPT_UNWRAP(cwd);
                    OPTION(CharPtr)
                    path = OPT_FROM_NULLABLE(CharPtr, pretty_path(ucwd));
                    free(ucwd);
                    if (IS_SOME(path)) {
                        char *upath = OPT_UNWRAP(path);
                        my_putstr(upath);
                        free(upath);
                    }
                }
            } break;
            case 'W': {
                OPTION(CharPtr)
                cwd = OPT_FROM_NULLABLE(CharPtr, getcwd(0, 0));
                if (IS_SOME(cwd)) {
                    char *ucwd = OPT_UNWRAP(cwd);
                    OPTION(CharPtr)
                    path = OPT_FROM_NULLABLE(CharPtr, basename(ucwd));
                    if (IS_SOME(path)) {
                        char *upath = OPT_UNWRAP(path);
                        my_putstr(upath);
                        free(ucwd);
                    }
                }
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
        } else {
            my_putchar(ps1[i]);
        }
    }
    fflush(stdout);
}
