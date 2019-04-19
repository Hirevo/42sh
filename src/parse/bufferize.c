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
                return NULL;
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
        for (; str[i] && !is_space(str[i]); i++) {
            for (size_t i2 = 0; delim[i2]; i2++)
                if (lstr_starts_with(str + i, delim[i2]))
                    return SOME(SizeT, i);
            if (str[i] == '\\')
                i += !!(str[i + 1]);
        }
        return SOME(SizeT, i);
    }
}

char **bufferize(char *str, int n)
{
    size_t i = 0;
    size_t args = 0;
    char **final = calloc(n + 1, sizeof(char *));
    OPTION(SizeT) len = NONE(SizeT);

    if (final == NULL)
        return NULL;
    while (str[i])
        if (is_space(str[i]))
            i += 1;
        else {
            len = arg_length(str + i);
            if (IS_NONE(len))
                return NULL;
            final[args] = strndup(str + i, OPT_UNWRAP(len));
            if (final[args] == NULL)
                return NULL;
            i += OPT_UNWRAP(len);
            args += 1;
        }
    final[args] = NULL;
    return final;
}

int count_link(char **final)
{
    int i = 0;

    while (final[i] &&
        (strcmp(final[i], "|") && strcmp(final[i], ";") &&
            strcmp(final[i], "||") && strcmp(final[i], "&&")))
        i += 1;
    return i;
}

void prepare_link(shell_t *shell, command_t *elem, int i, int last)
{
    if (shell->final[i] == NULL)
        elem->link = '0';
    else if (strcmp(shell->final[i], "&&") == 0)
        elem->link = 'e';
    else if (strcmp(shell->final[i], "||") == 0)
        elem->link = 'o';
    else
        elem->link = shell->final[i][0];
    shell->final[i] = NULL;
    char **tab = shell->final + last;
    size_t size = 0;
    for (size = 0; tab[size]; size++);
    lvec_reserve(elem->av, size);
    for (size = 0; tab[size]; size++)
        lvec_push_back(elem->av, 1, strdup(tab[size]));
    (elem->link != '0') ? insert_char(&(shell->final[i]), elem->link) : NULL;
    elem->count = -1;
}

int set_commands(shell_t *shell)
{
    command_t *elem;
    command_t *head;
    int i;
    int last;

    shell->commands = NULL;
    head = NULL;
    i = -1;
    while (shell->final[++i]) {
        elem = calloc(1, sizeof(*elem));
        if (elem == NULL)
            return -1;
        elem->av = lvec_new();
        elem->next = NULL;
        (head) ? (head->next = elem) : (shell->commands = elem);
        elem->prev = head;
        last = i;
        i += count_link(shell->final + i);
        if (i == last)
            return eputstr("invalid null command.\n"), -1;
        prepare_link(shell, elem, i, last);
        i -= (elem->link == '0');
        head = elem;
    }
    return 0;
}
