/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** echo
*/

#include "my.h"
#include <stdio.h>
#include <string.h>

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

void print_char(char *c, int *i)
{
    if (c[*i] == '\\')
        switch (c[++(*i)]) {
        case 'a':
            my_putchar('\a');
            break;
        case 'b':
            my_putchar('\b');
            break;
        case 'f':
            my_putchar('\f');
            break;
        case 'n':
            my_putchar('\n');
            break;
        case 'r':
            my_putchar('\r');
            break;
        case 't':
            my_putchar('\t');
            break;
        case 'v':
            my_putchar('\v');
            break;
        case 'e':
            my_putchar('\e');
            break;
        case '\\':
            my_putchar('\\');
            break;
        default:
            my_putchar('\\');
            my_putchar(c[*i]);
            break;
        }
    else
        my_putchar(c[*i]);
}

int echo_term(char **args)
{
    int flag_n = (args[0] && !strcmp(args[0], "-n"));
    int i = flag_n - 1;

    while (args[++i]) {
        if (i - (flag_n))
            my_putchar(' ');
        int j = -1;
        while (args[i][++j])
            print_char(args[i], &j);
    }
    if (!flag_n)
        my_putchar('\n');
    return 0;
}
