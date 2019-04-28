/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** op_low
*/

#include "parser_ll.h"
#include "shell.h"

int check_op_low(t_token **new, t_grammar *gram, char **tab, int *i)
{
    int j = -1;

    while (gram->op_low[++j]) {
        if (!strcmp(gram->op_low[j], tab[*i])) {
            (*new)->type = strdup("OP_LOW");
            (*new)->value = strdup(tab[*i]);
            return 1;
        }
    }
    return 0;
}
