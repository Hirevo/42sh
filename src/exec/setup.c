/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** setup
*/

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

void init_redirect(Command *head, int *r, int *l, int *i)
{
    *r = 0;
    *l = 0;
    *i = -1;
    head->r_name = NULL;
    head->r_type = NULL;
    head->l_name = NULL;
    head->l_type = NULL;
}

void skip_commands(Command **head, unsigned char ret)
{
    if ((*head) == NULL || (*head)->prev == NULL)
        return;
    const Command *prev = (*head)->prev;
    const bool should_skip = 
        (prev->link == 'e' && ret != 0) ||
        (prev->link == 'o' && ret == 0);
    if (should_skip) {
        (*head) = (*head)->next;
        skip_commands(head, ret);
    }
}
