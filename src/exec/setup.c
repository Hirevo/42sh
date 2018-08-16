/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** setup
*/

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

void init_redirect(command_t *head, int *r, int *l, int *i)
{
    *r = 0;
    *l = 0;
    *i = -1;
    head->r_name = NULL;
    head->r_type = NULL;
    head->l_name = NULL;
    head->l_type = NULL;
}

void setup_exec(command_t *head, int *fds, int ret)
{
    dup2(ret, 0);
    if (ret != 0)
        close(ret);
    if (head->next && head->link == '|')
        dup2(fds[1], 1);
    else if (head->r_type)
        if (setup_right_redirect(head, fds, (head->r_type[1] == 0)) == -1)
            exit(1);
}

void skip_commands(command_t **head, unsigned char ret)
{
    char last;

    if ((*head) &&
        (((*head)->link == 'e' && ret) || ((*head)->link == 'o' && !ret))) {
        last = (*head)->link;
        (*head) = (*head)->next;
        while ((*head) && (*head)->link != ';' && (*head)->link != 'e' &&
            (*head)->link != 'o')
            (*head) = (*head)->next;
        if ((*head) && (*head)->link == 'e' && last == 'o')
            ret = 1;
        if ((*head) && (*head)->link != ';')
            skip_commands(head, ret);
    }
}

void set_fground(shell_t *shell)
{
    setpgid(0, shell->pgid);
    if (shell->pgid == 0)
        tcsetpgrp(0, getpid());
}
