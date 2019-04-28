/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** nb_args
*/

int nb_args(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
        i += 1;
    return (i);
}
