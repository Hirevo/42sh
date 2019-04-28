/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_revstr
*/

int my_strlen(char *str)
{
    int count;

    count = 0;
    while (*str != '\0') {
        count = count + 1;
        str = str + 1;
    }
    return (count);
}

char *my_revstr(char *str)
{
    char buffer;
    int count;
    int reverse_count;

    count = 0;
    reverse_count = my_strlen(str) - 1;
    while (reverse_count >= 0) {
        buffer = *(str + count);
        *(str + count) = *(str - reverse_count);
        *(str - reverse_count) = buffer;
        reverse_count = reverse_count - 1;
        count = count + 1;
    }
    return (str);
}
