/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_str_isupper
*/

int my_str_isupper(char *str)
{
    int count;

    count = 0;
    while (str[count] != '\0') {
        if ((str[count] < 65 || str[count] > 90))
            return (0);
        count = count + 1;
    }
    return (1);
}
