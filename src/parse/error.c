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
            shell->exit_code = 1;
            free(shell->exit_str);
            shell->exit_str = my_unsigned_to_char(0);
            printf("Invalid null command.\n");
            return -1;
        }
    }
    return 0;
}
