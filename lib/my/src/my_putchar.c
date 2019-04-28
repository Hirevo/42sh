/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_putchar
*/

#include <unistd.h>

void my_putchar_printf(char c, int *count)
{
    *count += 1;
    write(1, &c, 1);
}

void my_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}
