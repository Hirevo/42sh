/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strlowcase
*/

char *my_strlowcase(char *str)
{
    int count;

    count = -1;
    while (str[++count] != 0)
        if (str[count] >= 'A' && str[count] <= 'Z')
            str[count] = str[count] + 32;
    return (str);
}
