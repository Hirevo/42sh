/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ast_lvl_build_branch
*/

#include "bs.h"
#include "parser_ll.h"

t_ast *rebuild_branch(t_ast *ast, t_ast *new, int count_ast)
{
    t_ast *tmp = ast;
    t_ast *father;

    while (tmp->father && count_ast > 0) {
        tmp = tmp->father;
        count_ast--;
    }
    if (!tmp->father)
        return rebuild_branch_start(tmp, new);
    father = tmp->father;
    new->father = father;
    if (father->right == tmp)
        father->right = new;
    else
        father->left = new;
    new->left = tmp;
    tmp->father = new;
    return new;
}

t_ast *create_simple_branch(t_ast *ast, t_ast *new)
{
    new->father = ast;
    if (!ast->left) {
        ast->left = new;
        ast = ast->left;
    }
    else if (!ast->right) {
        ast->right = new;
        ast = ast->right;
    }
    else {
        new->left = ast->right;
        ast->right->father = new->left;
        ast->right = new;
        ast = ast->right;
    }
    return ast;
}

t_ast *rebuild_branch_start(t_ast *ast, t_ast *new)
{
    new->left = ast;
    ast->father = new;
    return new;
}
