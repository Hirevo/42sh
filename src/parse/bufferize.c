/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** bufferize
*/

#include "auto_complete.h"
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
    int i1;
    int i2;
    char *ret;

    i1 = -1;
    i2 = 0;
    if (str[i1 + 1] == '"' || str[i1 + 1] == '\'')
        str = unquote_arg(str);
    ret = calloc(count_real_chars(str) + 1, sizeof(char));
    if (ret == NULL)
        return NULL;
    while (str[++i1])
        if (str[i1] == '\\')
            if (str[i1 + 1] == 0)
                return NULL;
            else {
                i1 += !!(str[i1 + 1]);
                ret[i2++] = str[i1];
            }
        else
            ret[i2++] = str[i1];
    ret[i2] = 0;
    free(str);
    return ret;
}

int arg_length(char *str)
{
    int i;
    char quote;

    i = 0;
    if (str[i] == '"' || str[i] == '\'') {
        quote = str[i++];
        while (str[i] && str[i] != quote) {
            if (str[i] == '\\')
                i += !!(str[i + 1]);
            i += 1;
        }
        return (str[i] == 0) ? -1 : (i + 1);
    }
    while (str[i] && !is_space(str[i])) {
        if (str[i] == '\\')
            i += !!(str[i + 1]);
        i += 1;
    }
    return i;
}

char **bufferize(char *str, int n)
{
    int i = 0;
    int args = 0;
    char **final = calloc(n + 1, sizeof(char *));
    int len;

    if (final == NULL)
        return NULL;
    while (str[i])
        if (is_space(str[i]))
            i += 1;
        else {
            len = arg_length(str + i);
            if (len == -1)
                return NULL;
            final[args] = strndup(str + i, len);
            if (final[args] == NULL)
                return NULL;
            i += len;
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
    elem->av = my_strarrdup(shell->final + last);
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
        elem->next = NULL;
        (head) ? (head->next = elem) : (shell->commands = elem);
        elem->prev = head;
        last = i;
        if ((i += count_link(shell->final + i)) == last)
            return ret_error(shell, "Invalid null command.\n");
        prepare_link(shell, elem, i, last);
        i -= (elem->link == '0');
        head = elem;
    }
    return 0;
}
