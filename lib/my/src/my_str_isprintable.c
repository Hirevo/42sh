/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_str_isprintable
*/

int my_str_isprintable(char *str)
{
    int count;

    count = 0;
    while (str[count] != '\0') {
        if ((str[count] < 33 || str[count] > 126))
            return (0);
        count = count + 1;
    }
    return (1);
}
