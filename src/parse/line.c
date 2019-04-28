/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** line
*/

#include "my.h"
#include "reports.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

char *my_epurstr(char *str)
{
    char *ret = calloc(strlen(str) + 1, sizeof(char));
    size_t i = 0;
    size_t j = 0;
    bool quoted = false;

    if (ret == NULL)
        return NULL;
    while (str[i]) {
        if (str[i] == '\\') {
            ret[j++] = str[i++];
            ret[j++] = str[i];
            if (str[i++] == 0)
                break;
        } else if (str[i] == '\'' && quoted == false) {
            ret[j++] = str[i++];
            while (str[i] && str[i] != '\'')
                ret[j++] = str[i++];
            if (str[i] == '\'')
                ret[j++] = str[i++];
        } else if (str[i] == '"') {
            quoted = !quoted;
            ret[j++] = str[i++];
        } else if (is_space(str[i]) && quoted == false) {
            ret[j++] = ' ';
            while (is_space(str[i]))
                i += 1;
        } else {
            ret[j++] = str[i++];
        }
    }
    free(str);
    return ret;
}

int count_links(char *str)
{
    int count = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == '\\')
            i += !!(str[i + 1]);
        else if (str[i] == '\'' || str[i] == '"') {
            char buf = str[i];
            size_t start = i;
            i += 1;
            while (str[i] && str[i] != buf)
                i += (str[i] == '\\' && buf != '\'') + 1;
            if (str[i] == 0) {
                report_unmatched_quote(str, start);
                return -1;
            }
        }
        count += is_separator(str[i]);
    }
    return count;
}

void skip_and_copy_string(char *str, int *i, char *ret, int *t)
{
    char quote = str[(*i)++];

    ret[(*t)++] = quote;
    while (str[*i] && str[*i] != quote) {
        if (str[*i] == '\\' && quote != '\'') {
            ret[(*t)++] = '\\';
            ret[(*t)++] = str[(*i) + 1];
            *i += !!(str[(*i) + 1]);
        } else
            ret[(*t)++] = str[*i];
        *i += 1;
    }
    ret[(*t)++] = str[(*i)];
}

void copy_escaped_char(char *str, int *i, char *ret, int *t)
{
    ret[(*t)++] = '\\';
    ret[(*t)++] = str[(*i) + 1];
    *i += !!(str[(*i) + 1]);
}

void my_epur_sep(char *ret, char *str, int *i, int *t)
{
    ret[(*t)++] = ' ';
    ret[(*t)++] = str[*i];
    if (str[*i] != ';' && str[*i + 1] == str[*i])
        ret[(*t)++] = str[++(*i)];
    ret[(*t)++] = ' ';
}

char *my_epurcommand(char *str)
{
    int i = count_links(str);
    char *ret = (i != -1) ? calloc(strlen(str) + 1 + i * 4, sizeof(char)) : 0;
    int t = 0;

    if (ret == NULL)
        return NULL;
    i = -1;
    while (str[++i])
        if (str[i] == '\\')
            copy_escaped_char(str, &i, ret, &t);
        else if (is_space(str[i])) {
            ret[t++] = ' ';
            while (is_space(str[++i]))
                ;
            i -= 1;
        } else if (str[i] == '"' || str[i] == '\'')
            skip_and_copy_string(str, &i, ret, &t);
        else if (is_separator(str[i]))
            my_epur_sep(ret, str, &i, &t);
        else
            ret[t++] = str[i];
    ret[t] = 0;
    free(str);
    return ret;
}
