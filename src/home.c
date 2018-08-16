/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** home
*/

#include "get_next_line.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

char *detect_home(char *temp, char *home)
{
    int i = 0;
    int j;

    if (home != NULL) {
        while (temp[i] == home[i] && temp[i] != 0)
            i += 1;
        if (home[i] == 0) {
            temp[0] = '~';
            i -= (home[i - 1] == '/');
            j = 1;
            while (temp[i] != 0) {
                temp[j] = temp[i];
                i += 1;
                j += 1;
            }
            temp[j] = 0;
        }
    }
    return temp;
}

char *get_current(char *current, char *home)
{
    char *temp = getcwd(0, 0);

    if (temp == NULL)
        return NULL;
    if (home && strcmp(home, "/"))
        temp = detect_home(temp, home);
    current[0] = 0;
    current = strcat(current, temp);
    free(temp);
    return current;
}
