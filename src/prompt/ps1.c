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

void ps1_prompt(Shell *shell)
{
    char *ps1 = OPT_UNWRAP_OR(OPT_FROM_NULLABLE(CharPtr, getenv("PS1")), "");

    fflush(stdout);
    for (size_t i = 0; ps1[i]; i++) {
        if (ps1[i] == '\\') {
            switch (ps1[++i]) {
            case 0:
                i -= 1;
            case '\\':
                writechar('\\');
                break;
            case 'h': {
                OPTION(CharPtr) hostname = get_hostname();
                if (IS_SOME(hostname)) {
                    char *hostname_u = OPT_UNWRAP(hostname);
                    ssize_t idx = lstr_index_of(hostname_u, 0, ".");
                    if (idx == -1)
                        writestr(hostname_u);
                    else
                        write(1, hostname_u, idx);
                    free(hostname_u);
                }
            } break;
            case 'H': {
                OPTION(CharPtr) hostname = get_hostname();
                OPT_AND_THEN(hostname, writestr);
                OPT_AND_THEN(hostname, free);
            } break;
            case 's':
                writestr("42sh");
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
                        writestr(upath);
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
                    pretty = OPT_FROM_NULLABLE(CharPtr, pretty_path(ucwd));
                    free(ucwd);
                    if (IS_SOME(pretty)) {
                        char *upretty = OPT_UNWRAP(pretty);
                        OPTION(CharPtr)
                        path = OPT_FROM_NULLABLE(CharPtr, basename(upretty));
                        if (IS_SOME(path)) {
                            char *upath = OPT_UNWRAP(path);
                            writestr(upath);
                            free(upretty);
                        }
                    }
                }
            } break;
            case 'u': {
                OPTION(CharPtr)
                login = OPT_FROM_NULLABLE(CharPtr, getenv("LOGNAME"));
                OPT_AND_THEN(login, writestr);
            } break;
            case '$':
                writechar(getuid() ? '$' : '#');
                break;
            case '?':
                my_put_nbr(shell->exit_code);
                break;
            case 'n':
                writechar('\n');
                break;
            case 't':
                writechar('\t');
                break;
            case 'a':
                writechar('\a');
                break;
            case 'r':
                writechar('\r');
                break;
            case 'e':
                writechar('\e');
                break;
            case 'g': {
                OPTION(CharPtr)
                branch = OPT_FROM_NULLABLE(CharPtr, show_cur_branch());
                OPT_AND_THEN(branch, writestr);
                OPT_AND_THEN(branch, free);
            } break;
            case '[':
            case ']':
            default:
                break;
            }
        } else {
            writechar(ps1[i]);
        }
    }
    fflush(stdout);
}
