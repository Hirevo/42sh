/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_str_islower
*/

int my_str_islower(char *str)
{
    int count;

    count = 0;
    while (str[count] != '\0') {
        if ((str[count] < 97 || str[count] > 122))
            return (0);
        count = count + 1;
    }
    return (1);
}
