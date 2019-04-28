/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strcapitalize
*/

char *my_strcapitalize(char *str)
{
    int count;

    count = 1;
    if (str[0] >= 97 && str[0] <= 122)
        str[0] = str[0] - 32;
    while (str[count] != '\0') {
        if (str[count] >= 'a' && str[count] <= 'z' &&
            (str[count - 1] < 'A' || str[count - 1] > 'Z') &&
            (str[count - 1] < 'a' || str[count - 1] > 'z') &&
            (str[count - 1] < '0' || str[count - 1] > '9'))
            str[count] = str[count] - 32;
        else if ((str[count] >= 'A' && str[count] <= 'Z') &&
            str[count - 1] != ' ')
            str[count] = str[count] + 32;
        count = count + 1;
    }
    return (str);
}
