/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_strcat
*/

char *my_strcat(char *dest, char *src)
{
    int count = 0;
    int i = 0;

    while (dest[count])
        count += 1;
    while (src[i]) {
        dest[count] = src[i];
        i += 1;
        count += 1;
    }
    dest[count] = '\0';
    return (dest);
}
