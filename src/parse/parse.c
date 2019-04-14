/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parse
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

void skip_string(char *str, int *i)
{
    char quote = str[(*i)++];

    while (str[*i]) {
        if (str[*i] == '\\' && quote != '\'')
            *i += (!!str[(*i) + 1]);
        else if (str[*i] != quote)
            break;
        *i += 1;
    }
    *i -= (str[*i] == 0);
}

unsigned int count_args(char *str)
{
    int i = -1;
    unsigned int args = 0;

    while (str[++i])
        if (str[i] == '\\')
            i += !!(str[i + 1]);
        else if (str[i] == '\'' || str[i] == '"') {
            skip_string(str, &i);
            args += 1;
        } else if (i == 0 && str[i] != ' ' && str[i] != '\t' &&
            !is_separator(str[i]))
            args += 1;
        else if ((str[i] != ' ' && str[i] != '\t') &&
            (str[i - 1] == ' ' || str[i - 1] == '\t'))
            args += 1;
    return args + 1;
}

int get_quoted_text(char *arg, char **final, int l, char c)
{
    int i = -1;
    int j = 1;

    while (arg[j] != c && arg[j] != 0) {
        if (arg[j] == '\\' && c != '\'')
            j += !!(arg[j]);
        j += 1;
    }
    if (arg[j++] == 0)
        return (c == '"') ? -3 : -4;
    *final = calloc(j + 1, sizeof(char));
    if (*final == NULL)
        return -1;
    while (arg[++i + 1] != c) {
        if (arg[i + 1] == '\\' && c != '\'')
            i += !!(arg[i + 2]);
        (*final)[i] = arg[i + 1];
    }
    (*final)[i] = 0;
    while (arg[j] && (arg[j] == ' ' || arg[j] == '\t'))
        j += 1;
    if (arg[j] == 0)
        return -2;
    return l + j;
}

int get_next_arg(char *arg, char **final, int l)
{
    int i = -1;
    int j = 0;

    arg += l;
    while (*arg == ' ' || *arg == '\t')
        arg += 1;
    if (*arg == '"' || *arg == '\'')
        return get_quoted_text(arg, final, l, *arg);
    while (arg[j] != ' ' && arg[j] != '\t' && arg[j] != '\'' &&
        arg[j] != '"' && arg[j] != 0)
        j += 1;
    *final = calloc(j + 1, sizeof(char));
    if (*final == NULL)
        return -1;
    while (++i < j)
        (*final)[i] = arg[i];
    (*final)[i] = 0;
    while ((arg[j] == ' ' || arg[j] == '\t') && arg[j] != 0)
        j += 1;
    if (arg[j] == 0)
        return -2;
    return l + j;
}

int count_entries(char *str)
{
    int i = -1;
    int args = 0;

    while (str[++i] != 0)
        if (i == 0 && str[i] != ':')
            args += 1;
        else if (str[i] != ':' && str[i - 1] == ':')
            args += 1;
    return args;
}

int get_next_entry(char *arg, char **final, int l)
{
    int i = -1;
    int j = 0;

    arg += l;
    while (*(arg) == ':')
        arg += 1;
    while (arg[++j] != ':' && arg[j] != 0)
        ;
    *final = calloc(j + 1, sizeof(char));
    if (*final == NULL)
        return -1;
    while (++i < j)
        (*final)[i] = arg[i];
    (*final)[i] = 0;
    while (arg[j] == ':' && arg[j] != 0)
        j += 1;
    if (arg[j] == 0)
        return -2;
    return l + j;
}
