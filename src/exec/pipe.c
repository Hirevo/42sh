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

OPTION(Int)
exec_branch(Shell *shell, Command **head, int fds[2], int *fd_carry)
{
    const bool to_fork = is_to_fork((*head)->link) || (*head)->next == NULL;

    if (to_fork == true) {
        const OPTION(Int) status = exec_redirected_builtins(shell, fds);
        if (IS_SOME(status)) {
            if (*fd_carry != 0)
                close(*fd_carry);
            skip_commands(head, OPT_UNWRAP(status));
            if (*head)
                (*head) = (*head)->next;
            return status;
        }
    }
    if ((*head)->l_type != 0)
        *fd_carry =
            setup_left_redirect((*head)->l_name, (*head)->l_type[1] == 0);
    pid_t pid = fork();
    if (pid == -1)
        return NONE(Int);

    int code = 0;
    if (pid) {
        code = father_action(head, fd_carry, fds, shell, pid);
    } else {
        exec_piped_child(*fd_carry, *head, fds, shell);
    }
    return SOME(Int, code);
}

OPTION(Int) exec_pipeline(Shell *shell)
{
    int fds[2];
    Command *head = shell->commands;
    OPTION(Int) status = NONE(Int);
    int fd_carry = 0;

    shell->fds = NULL;
    shell->pgid = 0;
    while (head) {
        shell->cur = head;
        if (head->link == '|' && pipe(fds) == -1)
            return eputstr("can't create pipe.\n"), NONE(Int);
        status = exec_branch(shell, &head, fds, &fd_carry);
        if (IS_NONE(status))
            break;
    }
    if (shell->tty && tcsetpgrp(0, getpgid(getpid())) == -1)
        perror("tcsetpgrp");
    return status;
}

void exec_piped_child(int ret, Command *head, int *fds, Shell *shell)
{
    signal(SIGINT, SIG_DFL);
    set_fground(shell);
    setup_exec(head, fds, ret);
    ret = 0;
    if (head->link == '|') {
        close(fds[0]);
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

int get_return(Shell *shell)
{
    int i = -1;
    int r = 0;
    int final = 0;

    while (shell->fds[++i])
        ;
    i -= 1;
    while (i >= 0) {
        waitpid(shell->fds[i], &r, 0);
        if (!WIFEXITED(r))
            diagnose_status(r);
        if (r && final == 0)
            final = r;
        i -= 1;
    }
    free(shell->fds);
    shell->fds = NULL;
    return final;
}

int father_action(Command **head, int *ret, int *fds, Shell *shell, pid_t pid)
{
    int r = 0;

    if (shell->pgid == 0)
        shell->pgid = pid;
    if (*ret != 0)
        close(*ret);
    if ((*head)->link == '|') {
        *ret = fds[0];
        close(fds[1]);
    } else
        *ret = 0;
    insert_int(&shell->fds, pid);
    if ((*head)->next == 0 || (*head)->link != '|') {
        r = get_return(shell);
        shell->pgid = 0;
    }
    skip_commands(head, WEXITSTATUS(r));
    if (*head)
        (*head) = (*head)->next;
    return WIFEXITED(r) ? WEXITSTATUS(r) : (WTERMSIG(r) + 128);
}
