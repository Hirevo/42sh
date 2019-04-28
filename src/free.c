/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** free
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <unistd.h>

void free_hist_entry(void *ctx, char **elem, size_t idx)
{
    (void)(ctx);
    (void)(idx);
    for (size_t i = 0; elem && elem[i]; i++)
        free(elem[i]);
    free(elem);
}

void free_hist(Shell *shell)
{
    lvec_for_each(shell->hist.arr,
        (void (*)(void *, void *, size_t))(free_hist_entry), 0);
    lvec_drop(shell->hist.arr);
}

void free_shell(Shell *shell)
{
    save_history(shell);
    free_hist(shell);
    save_alias(shell);
    lvec_clear(shell->fragments, true);
    lvec_drop(shell->fragments);
    lhmap_clear(shell->aliases, true);
    lhmap_drop(shell->aliases);
    lhmap_clear(shell->vars, true);
    lhmap_drop(shell->vars);
    lhmap_clear(shell->builtins, false);
    lhmap_drop(shell->builtins);
    free(shell->line);
    free_commands(shell);
    if (shell->tty) {
        writestr("exit\n");
        del_curterm(cur_term);
    }
}

void free_commands(Shell *shell)
{
    Command *head;
    Command *last;

    head = shell->commands;
    while (head) {
        lvec_clear(head->av, true);
        lvec_drop(head->av);
        head->av = NULL;
        free(head->r_type);
        free(head->r_name);
        free(head->l_type);
        free(head->l_name);
        last = head;
        head = head->next;
        free(last);
    }
}
