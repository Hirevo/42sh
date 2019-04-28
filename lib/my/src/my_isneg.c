/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_isneg
*/

#include "my.h"

void my_isneg(int n)
{
    if (n < 0)
        my_putchar('N');
    else
        my_putchar('P');
}
