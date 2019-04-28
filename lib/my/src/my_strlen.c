/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strlen
*/

int my_strlen(char *str)
{
    int count;

    count = 0;
    while (str && str[count] != 0)
        count = count + 1;
    return (count);
}

int my_strstrlen(char *str, char *c)
{
    int i;
    int e;

    i = -1;
    while (str[++i]) {
        e = -1;
        while (c[++e])
            if (str[i] == c[e])
                return (i);
    }
    return (i);
}
