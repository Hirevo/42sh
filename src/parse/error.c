/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** error
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int check_error(shell_t *shell)
{
    for (command_t *head = shell->commands; head; head = head->next) {
        if (((head->av == NULL || head->av[0] == NULL) && head->next) ||
            ((head->link == '|' || head->link == 'e' || head->link == 'o') &&
            !head->next)) {
            return eputstr("invalid null command.\n"), -1;
        }
    }
    return 0;
}