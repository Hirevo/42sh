/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ast_arg
*/

#include "parser_ll.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

static t_ast *set_left(t_ast *ast, t_ast *new, t_token *token)
{
    new = set_ast(new, token);
    new->father = ast;
    ast->left = new;
    return ast;
}

static t_ast *set_right(t_ast *ast, t_ast *new, t_token *token)
{
    new = set_ast(new, token);
    new->father = ast;
    ast->right = new;
    return ast;
}

t_ast *ast_arg(t_ast *ast, t_token *token)
{
    t_ast *new = calloc(1, sizeof(t_ast));

    if (new == 0)
        return NULL;
    if (!ast)
        return set_ast(new, token);
    if (!ast->left)
        return set_left(ast, new, token);
    return set_right(ast, new, token);
}
