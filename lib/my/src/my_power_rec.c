/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_power_rec
*/

int my_power_rec(int nb, int p)
{
    int resp_power_rec;

    resp_power_rec = 1;
    if (p == 0) {
        return (resp_power_rec);
    } else if (p < 0) {
        return (0);
    } else {
        resp_power_rec = nb;
        resp_power_rec = resp_power_rec * my_power_rec(nb, p - 1);
        return (resp_power_rec);
    }
}
