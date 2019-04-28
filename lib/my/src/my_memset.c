/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_memset
*/

void *my_memset(void *str, int c, int size)
{
    char *tmp;

    if (size) {
        size += 1;
        tmp = str;
        while (--size) {
            *tmp++ = c;
        }
    }
    return (str);
}
