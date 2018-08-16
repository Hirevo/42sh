/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_env
*/

#include "my.h"
#include "server.h"
#include <stdlib.h>

char *get_env(char *str)
{
    return getenv(str);
}
