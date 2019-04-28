/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** is_a_num
*/

int is_a_num(char *str)
{
    int i;

    i = 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i += 1;
    }
    return (1);
}
