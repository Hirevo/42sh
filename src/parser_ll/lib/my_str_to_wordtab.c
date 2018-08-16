/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** my_str_to_wordtab
*/

#include <stdlib.h>

static int to_parse(char c, char *parse)
{
    int j = -1;

    while (parse[++j] != '\0') {
        if (c == parse[j]) {
            return 0;
        }
    }
    return 1;
}

static int count_wordtab(char *str, char *parse)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (to_parse(str[i], parse) == 1 && str[i] != '\0') {
            count++;
            while (to_parse(str[i], parse) == 1 && str[i] != '\0') {
                i++;
            }
        }
        if (to_parse(str[i], parse) == 0 && str[i] != '\0')
            while (to_parse(str[i], parse) == 0 && str[i] != '\0') {
                i++;
            }
    }
    return count;
}

static int count_str(char *str, char *parse, int i)
{
    int mem = 0;

    while (to_parse(str[i + mem], parse) == 1 && str[i + mem])
        mem++;
    return mem;
}

char **bs_str_to_wordtab(char *str, char *parse)
{
    char **tab;
    int ijkl[4] = {0};

    if (str == 0)
        return 0;
    tab = calloc(count_wordtab(str, parse) + 1, sizeof(char *));
    if (tab == 0)
        return NULL;
    while (ijkl[3]++ < count_wordtab(str, parse)) {
        while (to_parse(str[ijkl[0]], parse) == 0 && str[ijkl[0]] != '\0')
            ijkl[0]++;
        ijkl[2] = 0;
        if (str[ijkl[0]] != '\0') {
            tab[ijkl[1]] =
                calloc(count_str(str, parse, ijkl[0]) + 1, sizeof(char));
            if (tab == 0)
                return 0;
            while (to_parse(str[ijkl[0]], parse) == 1 && str[ijkl[0]] != '\0')
                tab[ijkl[1]][ijkl[2]++] = str[ijkl[0]++];
            tab[ijkl[1]++][ijkl[2]] = '\0';
        }
    }
    tab[ijkl[1]] = NULL;
    return tab;
}
