/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** bufferize
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count_real_chars(char *str)
{
    int i = -1;
    int c = 0;

    while (str[++i]) {
        if (str[i] == '\\')
            i += !!(str[i + 1]);
        c += 1;
    }
    return c;
}

char *unquote_arg(char *str)
{
    int len = strlen(str) - 2;
    char *ret = strndup(str + 1, len);

    if (ret == NULL)
        return NULL;
    free(str);
    return ret;
}

char *format_arg(char *str)
{
    int i2 = 0;
    char quote = 0;

    if (str[0] == '"' || str[0] == '\'') {
        quote = str[0];
        str = unquote_arg(str);
    }
    if (quote == '\'')
        return str;
    char *ret = calloc(count_real_chars(str) + 1, sizeof(char));
    if (ret == NULL)
        return NULL;
    for (size_t i1 = 0; str[i1]; i1++) {
        if (str[i1] == '\\') {
            if (str[i1 + 1] == 0) {
                ret[i2++] = '\\';
            } else {
                i1 += !!(str[i1 + 1]);
                ret[i2++] = str[i1];
            }
        } else {
            ret[i2++] = str[i1];
        }
    }
    ret[i2] = 0;
    free(str);
    return ret;
}

OPTION(SizeT) arg_length(char *str)
{
    static const char *delim[] = {
        ">>",
        "<<",
        ">",
        "<",
        "||",
        "|",
        ";",
        "&&",
        "&",
        0,
    };

    if (str[0] == '"' || str[0] == '\'') {
        char quote = str[0];
        size_t i = 1;
        for (; str[i] && str[i] != quote; i++) {
            if (str[i] == '\\' && quote != '\'')
                i += !!(str[i + 1]);
        }
        return (str[i] == 0) ? NONE(SizeT) : SOME(SizeT, i + 1);
    } else {
        for (size_t i2 = 0; delim[i2]; i2++) {
            if (lstr_starts_with(str, delim[i2])) {
                return SOME(SizeT, strlen(delim[i2]));
            }
        }
        size_t i = 0;
        for (; str[i] && !is_space(str[i]) && !is_separator(str[i]); i++) {
            if (str[i] == '\\')
                i += !!(str[i + 1]);
        }
        return SOME(SizeT, i);
    }
}

vec_t *bufferize(char *str, int estimate)
{
    vec_t *fragments = lvec_with_capacity(estimate);
    if (fragments == NULL)
        return NULL;
    size_t i = 0;
    while (str[i])
        if (is_space(str[i])) {
            i += 1;
        } else {
            OPTION(SizeT) len = arg_length(str + i);
            if (IS_NONE(len))
                return NULL;
            char *arg = strndup(str + i, OPT_UNWRAP(len));
            if (arg == NULL) {
                lvec_clear(fragments, true);
                lvec_drop(fragments);
                return NULL;
            }
            lvec_push_back(fragments, 1, arg);
            i += OPT_UNWRAP(len);
        }
    return fragments;
}

int count_link(vec_t *fragments, size_t idx)
{
    size_t size = idx;

    while (size < lvec_size(fragments)) {
        char *fragment = lvec_at(fragments, size);
        if (!fragment || fragment[0] == '|' || fragment[0] == ';' ||
            fragment[0] == '&')
            return size - idx;
        size += 1;
    }
    return size - idx;
}

void prepare_link(Shell *shell, Command *elem, size_t i, size_t last)
{
    if (i >= lvec_size(shell->fragments))
        elem->link = '0';
    else if (lstr_equals(lvec_at(shell->fragments, i), "&&"))
        elem->link = 'e';
    else if (lstr_equals(lvec_at(shell->fragments, i), "||"))
        elem->link = 'o';
    else
        elem->link = ((char *)(lvec_at(shell->fragments, i)))[0];
    size_t size = i - last;
    lvec_reserve(elem->av, size);
    for (size = 0; size < lvec_capacity(elem->av); size++)
        lvec_push_back(
            elem->av, 1, strdup(lvec_at(shell->fragments, last + size)));
    elem->count = -1;
}

int set_commands(Shell *shell)
{
    Command *elem = NULL;
    Command *head = NULL;
    size_t last = 0;

    shell->commands = NULL;
    for (size_t i = 0; i < lvec_size(shell->fragments); i++) {
        elem = calloc(1, sizeof(*elem));
        if (elem == NULL)
            return -1;
        elem->av = lvec_new();
        elem->next = NULL;
        (head) ? (head->next = elem) : (shell->commands = elem);
        elem->prev = head;
        last = i;
        i += count_link(shell->fragments, i);
        if (i == last)
            return eputstr("invalid null command.\n"), -1;
        prepare_link(shell, elem, i, last);
        i -= (elem->link == '0');
        head = elem;
    }
    return 0;
}
