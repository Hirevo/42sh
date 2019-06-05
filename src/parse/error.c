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

bool check_errors(Command *commands)
{
    for (Command *head = commands; head; head = head->next) {
        if ((lvec_front(head->av) == NULL && head->next) ||
            ((head->link == '|' || head->link == 'e' || head->link == 'o') &&
                !head->next)) {
            eputstr("invalid null command.\n");
            return false;
        }
    }
    return true;
}
