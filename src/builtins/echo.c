/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** echo
*/

#include "shell.h"

char get_escaped_char(char c)
{
    switch (c) {
    case 0:
    case '\\':
        return '\\';
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'e':
        return '\e';
    case 'f':
        return '\f';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    default:
        return c;
    }
}

void print_char(char *c, size_t *i)
{
    if (c[*i] == '\\')
        switch (c[++(*i)]) {
        case 0:
            (*i)--;
        case '\\':
            writechar('\\');
            break;
        case 'a':
            writechar('\a');
            break;
        case 'b':
            writechar('\b');
            break;
        case 'f':
            writechar('\f');
            break;
        case 'n':
            writechar('\n');
            break;
        case 'r':
            writechar('\r');
            break;
        case 't':
            writechar('\t');
            break;
        case 'v':
            writechar('\v');
            break;
        case 'e':
            writechar('\e');
            break;
        default:
            writechar('\\');
            writechar(c[*i]);
            break;
        }
    else
        writechar(c[*i]);
}

int echo_b(Shell *shell, vec_t *args)
{
    (void)(shell);
    bool flag_n = (lvec_size(args) > 1 && lstr_equals(lvec_at(args, 1), "-n"));
    size_t first = flag_n + 1;

    for (size_t i = first; i < lvec_size(args); i++) {
        if (i != first)
            writechar(' ');
        char *arg = lvec_at(args, i);
        for (size_t j = 0; arg[j]; j++)
            print_char(arg, &j);
    }
    if (!flag_n)
        writechar('\n');
    return 0;
}
