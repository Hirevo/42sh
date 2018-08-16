/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** redir
*/

#include "bs.h"
#include "parser_ll.h"

int check_redir(t_token **new, t_grammar *gram, char **tab, int *i)
{
    int j = -1;

    while (gram->redir[++j]) {
        if (!strcmp(gram->redir[j], tab[*i])) {
            (*new)->type = strdup("REDIR");
            (*new)->value = strdup(tab[*i]);
            return 1;
        }
    }
    return 0;
}
