/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ast_lvl
*/

#include "bs.h"
#include "parser_ll.h"
#include <stdlib.h>
#include <string.h>

static int check_level(t_ast *ast)
{

    if (!strcmp(ast->type, "OP_LOW"))
        return 3;
    if (!strcmp(ast->type, "REDIR"))
        return 2;
    if (!strcmp(ast->type, "OP_HIGH"))
        return 1;
    return 0;
}

static int count_level_ast(t_ast *ast, int lvl_new)
{
    t_ast *tmp = ast;
    int count = 0;

    if (check_level(ast) == lvl_new) {
        return 0;
    }
    while (tmp->father && check_level(tmp) <= lvl_new &&
        check_level(tmp->father) <= lvl_new) {
        tmp = tmp->father;
        count++;
    }
    return count;
}

static t_ast *set_ast_level(t_ast *ast, t_ast *new)
{
    int lvl_new = check_level(new);
    int count_ast = count_level_ast(ast, lvl_new);

    if (count_ast || (!count_ast && lvl_new > check_level(ast)))
        return rebuild_branch(ast, new, count_ast);
    if (!ast->father && check_level(new) >= check_level(ast))
        return rebuild_branch_start(ast, new);
    return create_simple_branch(ast, new);
}

t_ast *ast_level(t_ast *ast, t_token *token)
{
    t_ast *new = calloc(1, sizeof(t_ast));

    if (new == 0)
        return NULL;
    set_ast(new, token);
    if (!ast) {
        return new;
    }
    if (!strcmp(ast->type, "ARG") && !ast->father) {
        ast->father = new;
        new->left = ast;
        return set_ast(new, token);
    }
    return set_ast_level(ast, new);
}
