/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** print_ast
*/

#include <bs.h>
#include <parser_ll.h>

static void rec_print(t_ast *ast)
{
    t_ast *left = ast;
    t_ast *right = ast;

    if (!ast) {
        printf("AST est NULL\n");
        return;
    }
    printf(">> %s <<\n", ast->value);
    if (ast->left) {
        left = ast->left;
        printf("-Left-");
        rec_print(left);
    }
    if (ast->right) {
        right = ast->right;
        printf("-Right-");
        rec_print(right);
    }
    printf("!!! UP (Father) !!!\n");
}

void print_ast(t_ast *ast)
{
    if (!ast) {
        printf("AST est NULL\n");
        return;
    }
    printf("\n");
    while (ast->father)
        ast = ast->father;
    printf("====START====\n");
    rec_print(ast);
    printf("=====END=====\n");
}
