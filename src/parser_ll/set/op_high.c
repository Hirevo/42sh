/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** op_high
*/

#include "parser_ll.h"
#include "shell.h"

int check_op_high(t_token **new, t_grammar *gram, char **tab, int *i)
{
    int j = -1;

    while (gram->op_high[++j]) {
        if (!strcmp(gram->op_high[j], tab[*i])) {
            (*new)->type = strdup("OP_HIGH");
            (*new)->value = strdup(tab[*i]);
            return 1;
        }
    }
    return 0;
}
