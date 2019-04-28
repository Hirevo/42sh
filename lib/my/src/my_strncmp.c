/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strncmp
*/

int my_strncmp(char *str1, char *str2, int n)
{
    int i;

    i = 0;
    while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
        i += 1;
    if (i == n)
        return (0);
    return (str2[i] - str1[i]);
}
