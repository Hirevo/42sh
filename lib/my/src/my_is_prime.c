/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_is_prime
*/

int my_is_prime(int nb)
{
    int interval_prime;

    if (nb <= 0)
        return (0);
    else {
        interval_prime = nb / 2;
        if (nb > 10000)
            interval_prime = nb / 100;
        if (nb > 1000000)
            interval_prime = nb / 1000;
        if (nb > 1000000000)
            interval_prime = nb / 100000;
        while ((nb % interval_prime) != 0 && interval_prime > 1) {
            interval_prime = interval_prime - 1;
            if (interval_prime == 1)
                return (1);
        }
        return (0);
    }
}
