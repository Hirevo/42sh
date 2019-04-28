/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** token
*/

#include "parser_ll.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

static t_token *set_token(t_token *token, t_grammar *gram, char **tab, int *i)
{
    t_token *tmp;
    t_token *new = calloc(1, sizeof(t_token));

    if (new == 0)
        return NULL;
    token = token ? token : new;
    tmp = token;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = (tmp == new) ? 0 : new;
    new->prev = (tmp == new) ? 0 : tmp;
    if (check_op_high(&new, gram, tab, i))
        return token;
    else if (check_op_low(&new, gram, tab, i))
        return token;
    else if (check_redir(&new, gram, tab, i))
        return token;
    else {
        set_arg(&new, gram, tab, i);
        (*i)--;
    }
    return token;
}

void my_free_tab(char **tab)
{
    for (size_t i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

t_token *fill_token(t_token *token, char *str)
{
    char **tab;
    t_grammar gram;
    int i = -1;

    gram.op_high = my_split(OP_HIGH, " ");
    gram.op_low = my_split(OP_LOW, " ");
    gram.redir = my_split(REDIR, " ");
    tab = my_split(str, " ");
    while (tab[++i])
        token = set_token(token, &gram, tab, &i);
    my_free_tab(gram.op_high);
    my_free_tab(gram.op_low);
    my_free_tab(gram.redir);
    my_free_tab(tab);
    return token;
}
