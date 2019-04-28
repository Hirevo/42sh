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

int check_error(Shell *shell)
{
    for (Command *head = shell->commands; head; head = head->next) {
        if ((lvec_front(head->av) == NULL && head->next) ||
            ((head->link == '|' || head->link == 'e' || head->link == 'o') &&
                !head->next)) {
            return eputstr("invalid null command.\n"), -1;
        }
    }
    return 0;
}
