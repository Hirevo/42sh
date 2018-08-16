/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** close
*/

#include <unistd.h>

int close_pipes(int *pipes)
{
    int i;

    i = -1;
    while (pipes[++i])
        close(pipes[i]);
    return 0;
}
