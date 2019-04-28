/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strupcase
*/

char *my_strupcase(char *str)
{
    int count;

    count = 0;
    while (str[count] != '\0') {
        if (str[count] >= 97 && str[count] <= 122)
            str[count] = str[count] - 32;
        count = count + 1;
    }
    return (str);
}
