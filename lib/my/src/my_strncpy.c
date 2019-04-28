/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strncpy
*/

char *my_strncpy(char *dest, char *src, int n)
{
    int count;

    count = 0;
    while (n > 0) {
        dest[count] = src[count];
        count = count + 1;
        n = n - 1;
    }
    dest[count] = 0;
    return (dest);
}
