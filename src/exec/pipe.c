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
    size_t final = (size_t)(acc);
    pid_t pid = (pid_t)(elem);
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

void skip_commands(Command **head, unsigned char ret)
{
    if ((*head) == NULL || (*head)->prev == NULL)
        return;
    const Command *prev = (*head)->prev;
    const bool should_skip =
        (prev->link == 'e' && ret != 0) || (prev->link == 'o' && ret == 0);
    if (should_skip) {
        (*head) = (*head)->next;
        skip_commands(head, ret);
    }
}

bool redirects_fd(void *ctx, void *elem, size_t idx)
{
    Redirect *redirect = (Redirect *)(elem);
    size_t fd = (size_t)(ctx);

    (void)(idx);
    return (redirect->from_fd == fd);
}

OPTION(Int) exec_pipeline(Shell *shell, Command *commands)
{
    int fds[2];
    Command *head = commands;
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

            bool stdin_redirected =
                lvec_any(head->redirects, redirects_fd, (void *)(0));
            bool stdout_redirected =
                lvec_any(head->redirects, redirects_fd, (void *)(1));
            bool stderr_redirected =
                lvec_any(head->redirects, redirects_fd, (void *)(2));

            OPTION(Int) saved_stdin = NONE(Int);
            if (stdin_redirected) {
                saved_stdin = SOME(Int, dup(0));
            }
            OPTION(Int) saved_stdout = NONE(Int);
            if (stdout_redirected) {
                saved_stdout = SOME(Int, dup(1));
            }
            OPTION(Int) saved_stderr = NONE(Int);
            if (stderr_redirected) {
                saved_stderr = SOME(Int, dup(2));
            }

            if (IS_SOME(fd_carry)) {
                int fd = OPT_UNWRAP(fd_carry);
                dup2(fd, 0);
                close(fd);
                fd_carry = NONE(Int);
            }

            for (size_t i = 0; i < lvec_size(head->redirects); i++) {
                Redirect *redirect = lvec_at(head->redirects, i);
                switch (redirect->type) {
                case REDIR_TYPE_SIMPLE_LEFT:
                    redirect_simple_left(redirect);
                    break;
                case REDIR_TYPE_SIMPLE_RIGHT:
                    redirect_simple_right(redirect);
                    break;
                case REDIR_TYPE_DOUBLE_LEFT:
                    redirect_double_left(redirect);
                    break;
                case REDIR_TYPE_DOUBLE_RIGHT:
                    redirect_double_right(redirect);
                    break;
                }
            }

            status = exec_builtins(shell, head->av);

            if (IS_SOME(saved_stdin)) {
                int fd = OPT_UNWRAP(saved_stdin);
                dup2(fd, 0);
                close(fd);
            }
            if (IS_SOME(saved_stdout)) {
                int fd = OPT_UNWRAP(saved_stdout);
                dup2(fd, 1);
                close(fd);
            }
            if (IS_SOME(saved_stderr)) {
                int fd = OPT_UNWRAP(saved_stderr);
                dup2(fd, 2);
                close(fd);
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
                if (shell->tty && pgid == 0) {
                    tcsetpgrp(0, getpid());
                }

                if (head->link == '|') {
                    close(fds[0]);
                }

                if (IS_SOME(fd_carry)) {
                    int fd = OPT_UNWRAP(fd_carry);
                    dup2(fd, 0);
                    close(fd);
                    fd_carry = NONE(Int);
                }

                if (head->next && head->link == '|') {
                    dup2(fds[1], 1);
                }

                if (head->link == '|') {
                    close(fds[1]);
                }

                for (size_t i = 0; i < lvec_size(head->redirects); i++) {
                    Redirect *redirect = lvec_at(head->redirects, i);
                    switch (redirect->type) {
                    case REDIR_TYPE_SIMPLE_LEFT:
                        redirect_simple_left(redirect);
                        break;
                    case REDIR_TYPE_SIMPLE_RIGHT:
                        redirect_simple_right(redirect);
                        break;
                    case REDIR_TYPE_DOUBLE_LEFT:
                        redirect_double_left(redirect);
                        break;
                    case REDIR_TYPE_DOUBLE_RIGHT:
                        redirect_double_right(redirect);
                        break;
                    }
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
