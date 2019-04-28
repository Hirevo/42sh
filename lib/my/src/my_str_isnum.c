/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_str_isnum
*/

int my_str_isnum(char *str)
{
    int count;

    count = 0;
    while (str[count] != 0) {
        if ((str[count] == '-' && count != 0) ||
            (str[count] < '0' || str[count] > '9'))
            return (0);
        count += 1;
    }
    return (1);
}
