/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_square_root
*/

int my_square_root(int nb)
{
    int interval;

    if (nb == 0)
        return (0);
    else if (nb == 1)
        return (1);
    else if (nb < 0)
        return (0);
    else {
        interval = nb / 2;
        if (nb > 10000)
            interval = nb / 100;
        if (nb > 1000000)
            interval = nb / 1000;
        if (nb > 1000000)
            interval = nb / 10000;
        while ((interval * interval) != nb && interval > 0) {
            interval = interval - 1;
        }
        return (interval);
    }
}
