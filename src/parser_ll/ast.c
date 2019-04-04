/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ast
*/

#include "bs.h"
#include "parser_ll.h"
#include <stdlib.h>
#include <string.h>

static t_ast *set_ast_right(t_ast *ast, char *type, char *value)
{
    t_ast *new = calloc(1, sizeof(t_ast));

    if (new == 0)
        return NULL;
    ast->right = new;
    new->father = ast;
    new->type = strdup(type);
    new->value = strdup(value);
    return ast;
}

static t_ast *ast_rec(t_ast *ast, t_token *token)
{
    if (!token->next && token->prev)
        return set_ast_right(ast, token->type, token->value);
    if (!token->next && !token->prev)
        return ast_arg(ast, token);
    if (!strcmp(token->type, "ARG"))
        ast = ast_arg(ast, token);
    else
        ast = ast_level(ast, token);
    token = token->next;
    return ast_rec(ast, token);
}

t_ast *set_ast(t_ast *ast, t_token *token)
{
    ast->type = strdup(token->type);
    ast->value = strdup(token->value);
    return ast;
}

t_ast *create_ast(t_ast *ast, t_token *token)
{
    if (!token)
        return calloc(1, sizeof(t_ast));
    while (token->prev)
        token = token->prev;
    ast = ast_rec(ast, token);
    while (ast->father)
        ast = ast->father;
    return ast;
}
