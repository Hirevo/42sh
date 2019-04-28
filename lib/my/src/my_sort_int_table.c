/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_sort_int_table
*/

#include "my.h"

int *my_sort_int_tab(int *tab, int size)
{
    int trouble;
    int i;

    trouble = 1;
    while (trouble) {
        i = 0;
        trouble = 0;
        while (i < size) {
            if (tab[i] > tab[i + 1]) {
                my_swap(tab[i], tab[i + 1]);
                trouble = 1;
            }
            i = i + 1;
        }
    }
    return (tab);
}
