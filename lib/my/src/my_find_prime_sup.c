/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_find_prime_sup
*/

#include "my.h"

int my_find_prime_sub(int n)
{
    long nb = n;

    if (nb <= 0)
        return (2);
    while (my_is_prime(nb) != 1 && nb < 2147483648) {
        nb = nb + 1;
        if (nb == 2147483648)
            return (0);
    }
    return (nb);
}
