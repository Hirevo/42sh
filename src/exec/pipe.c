/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** pipe
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void *inspect_exit_code(void *ctx, void *acc, void *elem, size_t idx)
{
    size_t final = ((size_t)(acc));
    pid_t pid = ((pid_t)(elem));
    int ret = 0;

    (void)(ctx);
    (void)(idx);
    waitpid(pid, &ret, 0);
    if (!WIFEXITED(ret))
        diagnose_status(ret);
    if (ret && final == 0)
        final = ret;
    return ((void *)(final));
}

OPTION(Int) exec_pipeline(Shell *shell)
{
    int fds[2];
    Command *head = shell->commands;
    OPTION(Int) status = NONE(Int);
    OPTION(Int) fd_carry = NONE(Int);
    size_t pgid = 0;
    vec_t *pid_list = lvec_with_capacity(1);

    while (head) {
        if (head->link == '|' && pipe(fds) == -1) {
            eputstr("can't create pipe.\n");
            return NONE(Int);
        }

        const bool builtin_exec = head->link == ';' || head->link == 'e' ||
            head->link == 'o' || head->next == NULL;

        if (builtin_exec == true &&
            lhmap_get(shell->builtins, lvec_front(head->av))) {

            OPTION(Int) save_in = NONE(Int);
            if (IS_SOME(fd_carry)) {
                int fd = OPT_UNWRAP(fd_carry);
                save_in = SOME(Int, dup(0));
                dup2(fd, 0);
                close(fd);
                fd_carry = NONE(Int);
            } else if (head->l_type) {
                save_in = SOME(Int, dup(0));
                OPTION(Int)
                in = setup_left_redirect(head, head->l_type[1] == 0);
                if (IS_SOME(in)) {
                    close(OPT_UNWRAP(in));
                }
            }

            OPTION(Int) save_out = NONE(Int);
            if (head->r_type) {
                save_out = SOME(Int, dup(1));
                OPTION(Int)
                out = setup_right_redirect(head, head->r_type[1] == 0);
                if (IS_SOME(out)) {
                    close(OPT_UNWRAP(out));
                }
            }

            status = exec_builtins(shell, head->av);

            if (IS_SOME(save_in)) {
                int fd = OPT_UNWRAP(save_in);
                dup2(fd, 0);
                close(fd);
            }
            if (IS_SOME(save_out)) {
                int fd = OPT_UNWRAP(save_out);
                fflush(stdout);
                dup2(fd, 1);
                close(fd);
            }

            if (IS_SOME(fd_carry)) {
                close(OPT_UNWRAP(fd_carry));
                fd_carry = NONE(Int);
            }

            if (IS_NONE(status)) {
                eputstr("%s: command not found.\n", lvec_front(head->av));
                status = SOME(Int, 1);
            }

            head = head->next;
            skip_commands(&head, OPT_UNWRAP(status));
        } else {
            pid_t pid = fork();
            if (pid == -1) {
                status = NONE(Int);
                break;
            } else if (pid > 0) {
                if (pgid == 0)
                    pgid = pid;

                if (IS_SOME(fd_carry)) {
                    close(OPT_UNWRAP(fd_carry));
                    fd_carry = NONE(Int);
                }

                if (head->link == '|') {
                    fd_carry = SOME(Int, fds[0]);
                    close(fds[1]);
                }

                lvec_push_back(pid_list, 1, (size_t)(pid));
                if (head->next == NULL || head->link != '|') {
                    lvec_reverse(pid_list);
                    size_t final = ((size_t)(
                        lvec_reduce(pid_list, inspect_exit_code, 0, 0)));
                    lvec_clear(pid_list, false);
                    status = SOME(Int,
                        WIFEXITED(final) ? WEXITSTATUS(final) :
                                           (WTERMSIG(final) + 128));
                    pgid = 0;
                    head = head->next;
                    skip_commands(&head, OPT_UNWRAP(status));
                } else {
                    head = head->next;
                }
            } else {
                signal(SIGINT, SIG_DFL);
                setpgid(0, pgid);
                if (shell->tty && pgid == 0)
                    tcsetpgrp(0, getpid());

                if (head->link == '|') {
                    close(fds[0]);
                }

                if (IS_SOME(fd_carry)) {
                    int fd = OPT_UNWRAP(fd_carry);
                    dup2(fd, 0);
                    close(fd);
                    fd_carry = NONE(Int);
                } else if (head->l_type) {
                    OPTION(Int)
                    in = setup_left_redirect(head, head->l_type[1] == 0);
                    if (IS_SOME(in)) {
                        close(OPT_UNWRAP(in));
                    }
                }

                if (head->next && head->link == '|') {
                    dup2(fds[1], 1);
                } else if (head->r_type) {
                    OPTION(Int)
                    out = setup_right_redirect(head, head->r_type[1] == 0);
                    if (IS_SOME(out)) {
                        close(OPT_UNWRAP(out));
                    }
                }

                if (head->link == '|') {
                    close(fds[1]);
                }

                if (is_path(lvec_front(head->av))) {
                    exec_process(head->av);
                    exit(1);
                }

                OPTION(Int) status = exec_builtins(shell, head->av);
                if (IS_NONE(status)) {
                    exec_process(head->av);
                    exit(1);
                }
                exit(OPT_UNWRAP(status));
            }
        }
    }

    lvec_clear(pid_list, false);
    lvec_drop(pid_list);

    if (shell->tty && tcsetpgrp(0, getpgid(getpid())) == -1)
        perror("tcsetpgrp");
    return status;
}
