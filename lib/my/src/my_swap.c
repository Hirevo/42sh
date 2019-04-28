/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_swap
*/

void my_swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
