/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** arg
*/

#include "bs.h"
#include "parser_ll.h"

static int check_is_arg(t_grammar *gram, char **tab, int *i)
{
    int j = -1;
    int count = 0;

    while (gram->op_high[++j]) {
        if (!strcmp(gram->op_high[j], tab[*i]))
            count++;
    }
    j = -1;
    while (gram->op_low[++j]) {
        if (!strcmp(gram->op_low[j], tab[*i]))
            count++;
    }
    j = -1;
    while (gram->redir[++j]) {
        if (!strcmp(gram->redir[j], tab[*i]))
            count++;
    }
    if (count == 0)
        return 1;
    return 0;
}

int set_arg(t_token **new, t_grammar *gram, char **tab, int *i)
{
    if (!check_is_arg(gram, tab, i))
        (*i)++;
    while (tab[*i] && check_is_arg(gram, tab, i)) {
        (*new)->type = strdup("ARG");
        if ((*new)->value) {
            (*new)->value = bs_strcat((*new)->value, " ");
            (*new)->value = bs_strcat((*new)->value, tab[*i]);
        }
        else
            (*new)->value = strdup(tab[*i]);
        (*i)++;
    }
    return 0;
}
