/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_putstr_fd
*/

void my_putstr_fd(char *str, int fd)
{
    int i;

    i = -1;
    while (str[++i] != 0)
        my_putchar(str[i], fd);
}
