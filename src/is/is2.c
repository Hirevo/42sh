/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** is2
*/

#include <stddef.h>

int is_separator(char c)
{
    return c == '>' || c == '<' || c == '|' || c == ';' || c == '&';
}

int is_space(char c)
{
    return c == ' ' || c == '\t';
}

int is_delimiter(char c)
{
    return c == ';' || c == '|' || c == '&';
}

int is_alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_');
}

int is_num(char *str)
{
    for (size_t i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
