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

int exec_branch(shell_t *shell, command_t **head, int fds[3], int *ret)
{
    int r = 0;

    if ((is_to_fork((*head)->link) || (*head)->next == NULL) &&
        exec_redirected_builtins(shell, fds[2], &r, fds) != 0) {
        if (*ret != 0)
            close(*ret);
        skip_commands(head, r);
        if (*head)
            (*head) = (*head)->next;
        return r;
    }
    if ((*head)->l_type)
        *ret = setup_left_redirect((*head)->l_name, (*head)->l_type[1] == 0);
    if ((fds[2] = fork()) == -1)
        return 84;
    fds[2] ? (r = father_action(head, ret, fds, shell)) :
             exec_piped_child(*ret, *head, fds, shell);
    return r;
}

int exec_pipeline(shell_t *shell)
{
    int fds[3];
    command_t *head;
    int ret;
    int r = 0;

    shell->fds = NULL;
    shell->pgid = 0;
    head = shell->commands;
    ret = 0;
    while (head) {
        shell->cur = head;
        fds[2] = -1;
        while (head->av[++(fds[2])])
            ;
        if (head->link == '|')
            if (pipe(fds) == -1)
                return (ret_error(shell, "Can't make pipe.\n"));
        if ((r = exec_branch(shell, &head, fds, &ret)) == 84)
            return 84;
    }
    if (tcsetpgrp(0, getpgid(getpid())) == -1)
        perror("tcsetpgrp");
    return r;
}

void exec_piped_child(int ret, command_t *head, int *fds, shell_t *shell)
{
    int i;

    signal(SIGINT, SIG_DFL);
    set_fground(shell);
    setup_exec(head, fds, ret);
    ret = -1 + 0 * (i = 0);
    if (head->link == '|') {
        close(fds[0]);
        close(fds[1]);
    }
    while (head->av[++ret])
        ;
    if (is_path(shell->cur->av[0]) || exec_builtins(shell, ret, &i) == 0)
        exec_child(shell);
    exit(i);
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
        if (r && !final)
            final = r;
        i -= 1;
    }
    free(shell->fds);
    shell->fds = NULL;
    return final;
}

int father_action(command_t **head, int *ret, int *fds, shell_t *shell)
{
    int r;

    if (shell->pgid == 0)
        shell->pgid = fds[2];
    if (*ret != 0)
        close(*ret);
    if ((*head)->link == '|') {
        *ret = fds[0];
        close(fds[1]);
    }
    else
        *ret = 0;
    insert_int(&shell->fds, fds[2]);
    r = 0;
    if (!((*head)->next) || (*head)->link != '|') {
        r = get_return(shell);
        shell->pgid = 0;
        fds[2] = -1;
    }
    skip_commands(head, WEXITSTATUS(r));
    if (*head)
        (*head) = (*head)->next;
    return WIFEXITED(r) ? WEXITSTATUS(r) : r % 128 + 128;
}
