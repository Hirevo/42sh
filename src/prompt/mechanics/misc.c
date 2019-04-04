/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** misc
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char get_input(void)
{
    char c = -1;

    read(0, &c, 1);
    return c;
}

void handle_error(char *msg)
{
    perror(msg);
    exit(84);
}
