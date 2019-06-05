/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** redirects
*/

#include "get_next_line.h"
#include "my.h"
#include "reports.h"
#include "shell.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

bool assign_redirects(Command *commands)
{
    Command *head = commands;
    Command *last = NULL;

    while (head) {
        for (size_t i = 0; i < lvec_size(head->av); i++) {
            OPTION(Redirect)
            opt_redirect = parse_redirect(lvec_at(head->av, i));
            if (IS_SOME(opt_redirect)) {
                Redirect redirect = OPT_UNWRAP(opt_redirect);

                switch (redirect.type) {
                case REDIR_TYPE_SIMPLE_LEFT:
                case REDIR_TYPE_DOUBLE_LEFT:
                    if (redirect.from_fd == 0 && last && last->link == '|')
                        return eputstr("ambiguous input redirect.\n"), false;
                    break;
                case REDIR_TYPE_SIMPLE_RIGHT:
                case REDIR_TYPE_DOUBLE_RIGHT:
                    if (redirect.from_fd == 1 && head->link == '|')
                        return eputstr("ambiguous output redirect.\n"), false;
                    break;
                default:
                    break;
                }

                lvec_remove(head->av, i);
                if (lvec_size(head->av) <= i) {
                    return eputstr("missing name for redirect.\n"), false;
                }
                char *dest = lvec_remove(head->av, i);
                if (lvec_size(head->av) == 0)
                    return eputstr("invalid null command.\n"), false;

                switch (redirect.kind) {
                case REDIR_KIND_FD:
                    if (is_num(dest) == 0) {
                        eputstr("%s: invalid file descriptor.\n", dest);
                        free(dest);
                        return false;
                    }
                    redirect.to_fd = strtoul(dest, 0, 10);
                    free(dest);
                    break;
                case REDIR_KIND_FILE:
                    redirect.to_name = dest;
                    break;
                default:
                    free(dest);
                    eputstr("unknown redirection kind.\n");
                    return false;
                }

                Redirect *ret = malloc(sizeof(Redirect));
                if (ret == 0)
                    return false;
                memcpy(ret, &redirect, sizeof(Redirect));
                lvec_push_back(head->redirects, 1, ret);

                i -= 1;
            }
        }
        last = head;
        head = head->next;
    }
    return true;
}
