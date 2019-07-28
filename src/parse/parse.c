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

void skip_string(char *str, size_t *idx)
{
    char quote = str[(*idx)++];

    while (str[*idx]) {
        if (str[*idx] == '\\')
            *idx += (!!str[(*idx) + 1]);
        else if (str[*idx] == quote)
            break;
        *idx += 1;
    }
    *idx -= (str[*idx] == 0);
}

size_t estimate_fragment_count(char *str)
{
    size_t args = 0;

    for (size_t idx = 0; str[idx]; idx++) {
        if (str[idx] == '\\') {
            idx += !!(str[idx + 1]);
        } else if (str[idx] == '\'') {
            idx += 1;
            while (str[idx] && str[idx] != '\'')
                idx += 1;
            idx -= (str[idx] == 0);
            args += 1;
        } else if (str[idx] == '"') {
            skip_string(str, &idx);
            args += 1;
        } else if (idx == 0 && !is_space(str[idx]) &&
            !is_separator(str[idx])) {
            args += 1;
        } else if (!is_space(str[idx]) && is_space(str[idx - 1])) {
            args += 1;
        }
    }
    return args;
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
    while (is_space(arg[j]))
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
    while (is_space(*arg))
        arg += 1;
    if (*arg == '"' || *arg == '\'')
        return get_quoted_text(arg, final, l, *arg);
    while (!is_space(arg[j]) && arg[j] != '\'' && arg[j] != '"' && arg[j] != 0)
        j += 1;
    *final = calloc(j + 1, sizeof(char));
    if (*final == NULL)
        return -1;
    while (++i < j)
        (*final)[i] = arg[i];
    (*final)[i] = 0;
    while (is_space(arg[j]))
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
