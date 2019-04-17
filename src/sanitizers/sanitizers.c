/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** construct
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

static int count_separators(char *str)
{
    int count = 0;

    for (size_t i = 0; str[i]; i++) {
        if (is_separator(str[i]) || is_space(str[i]) || str[i] == '\\' ||
            str[i] == '"' || str[i] == '\'' || str[i] == '`' ||
            str[i] == '$' || str[i] == '!')
            count += 1;
    }
    return count;
}

char *sanitize(char *str, bool to_free)
{
    int i2 = 0;
    int size = count_separators(str);
    char *ret = calloc(strlen(str) + (size * 2) + 1, sizeof(char));

    if (ret == NULL)
        return NULL;
    for (size_t i1 = 0; str[i1]; i1++) {
        if (str[i1] == '\\' || is_separator(str[i1]) || str[i1] == '"' ||
            str[i1] == '\'' || str[i1] == '`' ||
            str[i1] == '$' || str[i1] == '!') {
            ret[i2++] = '\\';
            ret[i2++] = str[i1];
        } else {
            ret[i2++] = str[i1];
        }
    }
    ret[i2] = 0;
    if (to_free)
        free(str);
    return ret;
}

char *sanitize_double_quotes(char *str, bool to_free)
{
    int i2 = 0;
    int size = count_separators(str);
    char *ret = calloc(strlen(str) + (size * 2) + 1, sizeof(char));

    if (ret == NULL)
        return NULL;
    for (size_t i1 = 0; str[i1]; i1++) {
        if (str[i1] == '\\' || str[i1] == '"' || str[i1] == '`' ||
            str[i1] == '$' || str[i1] == '!') {
            ret[i2++] = '\\';
            ret[i2++] = str[i1];
        } else {
            ret[i2++] = str[i1];
        }
    }
    ret[i2] = 0;
    if (to_free)
        free(str);
    return ret;
}