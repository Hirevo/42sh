/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** split_it
*/

#include <stdlib.h>

int is_in(char str, char *test)
{
    int i = -1;

    while (test[++i] != '\0') {
        if (test[i] == str)
            return 1;
    }
    return 0;
}

static int find_len(char *str, char *to_split)
{
    int i = 0;
    int c = 1;

    while (str[i]) {
        if (is_in(str[i], to_split))
            c++;
        i++;
    }
    return c + 1;
}

int word_length(char *str, int i, char *to_split)
{
    int c = 0;

    while (str[i + c] && !is_in(str[i + c], to_split)) {
        if (str[i + c] == '\\')
            c++;
        if (str[i + c])
            c++;
    }
    return c;
}

static char **cut_it(char *str, char **tab, char *to_split)
{
    int x;
    int y = 0;
    int i = 0;

    while (str[i]) {
        x = 0;
        if (!is_in(str[i], to_split)) {
            tab[y] = calloc(word_length(str, i, to_split) + 1, sizeof(char));
            if (tab[y] == NULL)
                return NULL;
            while (str[i] && !is_in(str[i], to_split))
                tab[y][x++] = str[i++];
            tab[y++][x] = '\0';
        }
        if (str[i])
            i++;
    }
    tab[y] = NULL;
    return tab;
}

char **split_it(char *str, char *to_split)
{
    char **tab = calloc(find_len(str, to_split), sizeof(char *));

    if (tab == NULL)
        return NULL;
    tab = cut_it(str, tab, to_split);
    if (tab == NULL)
        return NULL;
    return tab;
}
