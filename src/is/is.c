/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** is
*/

#include "my.h"
#include <string.h>
#include <sys/stat.h>

int is_right_redirect(char *str)
{
    return strcmp(str, ">") == 0 || strcmp(str, ">>") == 0;
}

int is_left_redirect(char *str)
{
    return strcmp(str, "<") == 0 || strcmp(str, "<<") == 0;
}

int is_to_fork(char c)
{
    return c == ';' || c == 'e' || c == 'o';
}
