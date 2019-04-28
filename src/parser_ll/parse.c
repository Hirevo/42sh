/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parse
*/

#include "parser_ll.h"
#include "shell.h"
#include <stdlib.h>

static void free_token(t_token **token)
{
    t_token *tmp;

    while ((*token)->next) {
        tmp = (*token);
        (*token) = (*token)->next;
        free(tmp->type);
        free(tmp->value);
        free(tmp);
    }
    free((*token)->type);
    free((*token)->value);
    free(*token);
}

t_ast *parser_ll(char *str)
{
    t_token *token = fill_token(0, str);
    t_ast *ast = create_ast(0, token);

    if (!str)
        return NULL;
    while (ast->father)
        ast = ast->father;
    while (token && token->prev)
        token = token->prev;
    if (token)
        free_token(&token);
    print_ast(ast);
    return ast;
}
