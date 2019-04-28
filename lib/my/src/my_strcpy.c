/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strcpy
*/

char *my_strcpy(char *dest, char *src)
{
    int count;

    count = -1;
    while (src[++count])
        dest[count] = src[count];
    dest[count] = 0;
    return (dest);
}
