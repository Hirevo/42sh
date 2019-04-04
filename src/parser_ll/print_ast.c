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
    if (!ast) {
        printf("No ast\n");
        return;
    }
    printf(">> '%s' <<\n", ast->value);
    if (ast->left) {
        printf("Left:\n");
        rec_print(ast->left);
    } else {
        printf("Left: None\n");
    }
    if (ast->right) {
        printf("Right:\n");
        rec_print(ast->right);
    } else {
        printf("Right: None\n");
    }
}

void print_ast(t_ast *ast)
{
    if (!ast) {
        printf("No ast\n");
        return;
    }
    printf("\n");
    while (ast->father)
        ast = ast->father;
    printf("====START====\n");
    rec_print(ast);
    printf("=====END=====\n");
}
