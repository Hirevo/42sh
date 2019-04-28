/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** size_nb
*/

int size_nb(int nb)
{
    int i;

    i = 1;
    while ((nb /= 10))
        i += 1;
    return (i);
}
