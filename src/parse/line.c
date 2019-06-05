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

char *my_epurcommand(char *str)
{
    int i = count_links(str);
    char *ret = (i != -1) ? calloc(strlen(str) + 1 + i * 4, sizeof(char)) : 0;
    size_t out = 0;

    if (ret == NULL)
        return NULL;
    for (size_t idx = 0; str[idx]; idx++) {
        if (str[idx] == '\\') {
            ret[out++] = '\\';
            ret[out++] = str[idx + 1];
            idx += !!(str[idx + 1]);
        } else if (is_space(str[idx])) {
            ret[out++] = ' ';
            idx += 1;
            while (is_space(str[idx]))
                idx += 1;
            idx -= 1;
        } else if (str[idx] == '"' || str[idx] == '\'') {
            char quote = str[idx++];
            ret[out++] = quote;
            while (str[idx] && str[idx] != quote) {
                if (str[idx] == '\\' && quote != '\'') {
                    ret[out++] = '\\';
                    ret[out++] = str[idx + 1];
                    idx += !!(str[idx + 1]);
                } else
                    ret[out++] = str[idx];
                idx += 1;
            }
            ret[out++] = str[idx];
        } else if (is_delimiter(str[i])) {
            ret[out++] = ' ';
            ret[out++] = str[idx];
            if (str[idx] != ';' && str[idx + 1] == str[idx])
                ret[out++] = str[++idx];
            ret[out++] = ' ';
        } else {
            OPTION(SizeT) opt_span = span_redirect(str + idx);
            if (IS_SOME(opt_span)) {
                size_t span = OPT_UNWRAP(opt_span);
                strncat(ret + out, str + idx, span);
                out += span;
                idx += span - 1;
                ret[out++] = ' ';
            } else {
                ret[out++] = str[idx];
            }
        }
    }
    ret[out] = 0;
    free(str);
    return ret;
}
