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

exec_status_t exec_branch(
    shell_t *shell, command_t **head, int fds[3], int *fd_carry)
{
    const bool to_fork = is_to_fork((*head)->link) || (*head)->next == NULL;

    if (to_fork == true) {
        const exec_status_t status =
            exec_redirected_builtins(shell, fds[2], fds);
        if (status.ok == true) {
            if (*fd_carry != 0)
                close(*fd_carry);
            skip_commands(head, status.code);
            if (*head)
                (*head) = (*head)->next;
            return status;
        }
    }
    if ((*head)->l_type != 0)
        *fd_carry =
            setup_left_redirect((*head)->l_name, (*head)->l_type[1] == 0);
    fds[2] = fork();
    if (fds[2] == -1)
        return (exec_status_t){
            .ok = false,
            .code = 1,
        };

    int code = 0;
    if (fds[2]) {
        code = father_action(head, fd_carry, fds, shell);
    } else {
        exec_piped_child(*fd_carry, *head, fds, shell);
    }
    return (exec_status_t){
        .ok = true,
        .code = code,
    };
}

exec_status_t exec_pipeline(shell_t *shell)
{
    int fds[3];
    command_t *head;
    exec_status_t status;
    int fd_carry;

    shell->fds = NULL;
    shell->pgid = 0;
    head = shell->commands;
    fd_carry = 0;
    while (head) {
        shell->cur = head;
        fds[2] = 0;
        while (head->av[fds[2]])
            fds[2] += 1;
        if (head->link == '|' && pipe(fds) == -1) {
            return (exec_status_t){
                .ok = false,
                .code = (eputstr("can't create pipe.\n"), -1),
            };
        }
        status = exec_branch(shell, &head, fds, &fd_carry);
        if (status.ok == false)
            break;
    }
    if (shell->tty && tcsetpgrp(0, getpgid(getpid())) == -1)
        perror("tcsetpgrp");
    return status;
}

void exec_piped_child(int ret, command_t *head, int *fds, shell_t *shell)
{
    exec_status_t status;

    signal(SIGINT, SIG_DFL);
    set_fground(shell);
    setup_exec(head, fds, ret);
    ret = 0;
    if (head->link == '|') {
        close(fds[0]);
        close(fds[1]);
    }
    while (head->av[ret])
        ret += 1;
    if (is_path(shell->cur->av[0])) {
        exec_child(shell);
        exit(1);
    }
    status = exec_builtins(shell, ret);
    if (status.ok == false) {
        exec_child(shell);
        exit(1);
    }
    exit(status.code);
}

int get_return(shell_t *shell)
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

int father_action(command_t **head, int *ret, int *fds, shell_t *shell)
{
    int r = 0;

    if (shell->pgid == 0)
        shell->pgid = fds[2];
    if (*ret != 0)
        close(*ret);
    if ((*head)->link == '|') {
        *ret = fds[0];
        close(fds[1]);
    } else
        *ret = 0;
    insert_int(&shell->fds, fds[2]);
    if ((*head)->next == 0 || (*head)->link != '|') {
        r = get_return(shell);
        shell->pgid = 0;
        fds[2] = -1;
    }
    skip_commands(head, WEXITSTATUS(r));
    if (*head)
        (*head) = (*head)->next;
    return WIFEXITED(r) ? WEXITSTATUS(r) : (r % 128 + 128);
}
