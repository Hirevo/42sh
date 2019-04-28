/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_puterror
*/

#include <unistd.h>

int my_puterror(char *str)
{
    int i;

    i = 0;
    while (str[i]) {
        write(2, &str[i], 1);
        i += 1;
    }
    return (i);
}
