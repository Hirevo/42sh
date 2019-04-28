/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strcmp
*/

int my_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i])
        i += 1;
    return (str1[i] - str2[i]);
}
