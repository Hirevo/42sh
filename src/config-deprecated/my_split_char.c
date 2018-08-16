/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** my_split_char
*/

#include <stdlib.h>

static int is_sep(char c, char sep)
{
    if (c == sep)
        return 1;
    return 0;
}

static int nb_par(char *str, char sep)
{
    int i = 0;
    int count = 0;

    while (str[i]) {
        if (!is_sep(str[i], sep)) {
            count += 1;
            while (str[i] && !is_sep(str[i], sep))
                i += 1;
        }
        if (str[i])
            i += 1;
    }
    return count;
}

static int index_child(char *str, char sep, int index)
{
    int i = 0;
    int count = 0;

    while (str[i] && is_sep(str[i], sep) && ++i)
        ;
    while (str[i] && count < index) {
        if (!is_sep(str[i], sep)) {
            count += 1;
            while (str[i] && !is_sep(str[i], sep))
                i += 1;
            if (str[i])
                i += 1;
        }
        while (str[i] && is_sep(str[i], sep) && i++)
            ;
    }
    if (is_sep(str[i], sep))
        i += 1;
    return i;
}

static int len_child(char *str, char sep, int index)
{
    int i = index_child(str, sep, index);
    int count = 0;

    while (str[i] && !is_sep(str[i], sep)) {
        count += 1;
        i += 1;
    }
    return count;
}

char **my_split_char(char *str, char sep)
{
    int i = -1;
    int j;
    int index;
    char **ret;

    if (str == NULL)
        return NULL;
    ret = calloc(nb_par(str, sep) + 1, sizeof(char *));
    if (ret == NULL)
        return NULL;
    ret[nb_par(str, sep)] = NULL;
    while (++i < nb_par(str, sep)) {
        j = 0;
        ret[i] = calloc(len_child(str, sep, i) + 1, sizeof(char));
        ret[i][len_child(str, sep, i)] = '\0';
        index = index_child(str, sep, i);
        while (j < len_child(str, sep, i)) {
            ret[i][j] = str[index];
            index += 1;
            j += 1;
        }
    }
    return ret;
}
