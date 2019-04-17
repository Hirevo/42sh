/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** echo
*/

#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char get_escaped_char(char c)
{
    if (c == 'a')
        return '\a';
    else if (c == 'b')
        return '\b';
    else if (c == 'e')
        return '\e';
    else if (c == 'f')
        return '\f';
    else if (c == 'n')
        return '\n';
    else if (c == 'r')
        return '\r';
    else if (c == 't')
        return '\t';
    else if (c == 'v')
        return '\v';
    else if (c == '\\')
        return '\\';
    return c;
}

void print_char(char *c, size_t *i)
{
    if (c[*i] == '\\')
        switch (c[++(*i)]) {
        case 'a':
            putchar('\a');
            break;
        case 'b':
            putchar('\b');
            break;
        case 'f':
            putchar('\f');
            break;
        case 'n':
            putchar('\n');
            break;
        case 'r':
            putchar('\r');
            break;
        case 't':
            putchar('\t');
            break;
        case 'v':
            putchar('\v');
            break;
        case 'e':
            putchar('\e');
            break;
        case '\\':
            putchar('\\');
            break;
        default:
            putchar('\\');
            putchar(c[*i]);
            break;
        }
    else
        putchar(c[*i]);
}

int echo_term(vec_t *args)
{
    bool flag_n = (lvec_at(args, 1) && !strcmp(lvec_at(args, 1), "-n"));
    size_t first = flag_n + 1;

    for (size_t i = first; i < lvec_size(args); i++) {
        if (i != first)
            putchar(' ');
        char *arg = lvec_at(args, i);
        for (size_t j = 0; arg[j]; j++)
            print_char(arg, &j);
    }
    if (!flag_n)
        putchar('\n');
    return 0;
}
