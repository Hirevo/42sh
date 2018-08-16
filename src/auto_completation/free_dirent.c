/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** free_dirent
*/

#include <dirent.h>
#include <stdlib.h>

void my_free_tab(void **tab)
{
    int i;

    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

void my_free_dirent(struct dirent **tab, int size)
{
    int i;

    i = 0;
    while (i < size)
        free(tab[i++]);
    free(tab);
}
