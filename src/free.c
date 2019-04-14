/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** free
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void free_hist_entry(void *ctx, char **elem, size_t idx)
{
    (void)(ctx);
    (void)(idx);
    for (size_t i = 0; elem && elem[i]; i++)
        free(elem[i]);
    free(elem);
}

void free_hist(shell_t *shell)
{
    lvec_for_each(shell->hist.arr,
        (void (*)(void *, void *, size_t))(free_hist_entry), 0);
    lvec_drop(shell->hist.arr);
}

void free_alias_entry(void *ctx, alias_t *elem, size_t idx)
{
    (void)(ctx);
    (void)(idx);
    free(elem->alias);
    free(elem->command);
    free(elem);
}

void free_alias(shell_t *shell)
{
    lhmap_clear(shell->alias, true);
    lhmap_drop(shell->alias);
}

void free_shell(shell_t *shell)
{
    save_history(shell);
    save_alias(shell);
    free_shell2(shell);
}

void free_shell2(shell_t *shell)
{
    int i;

    i = -1;
    if (shell->final != NULL) {
        while (shell->final[++i] != NULL)
            free(shell->final[i]);
        free(shell->final);
    }
    free_alias(shell);
    free(shell->last);
    free(shell->line);
    free_commands(shell);
    if (isatty(0))
        printf("exit\n");
}

void free_commands(shell_t *shell)
{
    int i;
    command_t *head;
    command_t *last;

    head = shell->commands;
    while (head) {
        i = -1;
        while (head->av[++i])
            free(head->av[i]);
        free(head->av);
        free(head->r_type);
        free(head->r_name);
        free(head->l_type);
        free(head->l_name);
        last = head;
        head = head->next;
        free(last);
    }
}
