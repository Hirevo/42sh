/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strncat
*/

char *my_strncat(char *dest, char *src, int size)
{
    int iteration;
    int i;
    int c;

    c = 0;
    i = 0;
    iteration = 0;
    while (dest[i] != '\0' && iteration < size) {
        i += 1;
        iteration += 1;
    }
    iteration = 0;
    while (src[c] != '\0' && iteration < size) {
        dest[i] = src[c];
        c += 1;
        i += 1;
        iteration += 1;
    }
    dest[i] = '\0';
    return (dest);
}
