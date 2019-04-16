/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** auto_list
*/

#include "auto_complete.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy_the_list(match_t **list)
{
    match_t *prev;
    match_t *temp = *list;

    while (temp) {
        prev = temp;
        free(temp->cmd);
        temp = temp->next;
        free(prev);
    }
    *list = NULL;
}

void show_autolist(shell_t *shell, match_t *list)
{
    match_t *tmp = list;
    char *str;
    char *cmd;

    if (!list)
        return;
    str = strdup("echo \"");
    printf("\n");
    while (tmp) {
        if (strcmp(tmp->cmd, "..") && strcmp(tmp->cmd, ".")) {
            if (asprintf(&cmd, "%s%s\\\\n", str,
                    sanitize_double_quotes(tmp->cmd, 0)) == -1)
                handle_error("calloc");
            free(str);
            str = cmd;
        }
        tmp = tmp->next;
    }
    if (asprintf(&cmd, "%s\" | sort | column", str) == -1)
        handle_error("calloc");
    free(str);
    str = cmd;
    quick_exec(shell, cmd);
}

int add_in_autolist(match_t **list, char *cmd)
{
    match_t *tmp;
    match_t *elem = calloc(1, sizeof(*elem));

    if (elem == NULL)
        return -1;
    elem->cmd = cmd;
    elem->next = NULL;
    if (*list == NULL) {
        *list = elem;
        return 0;
    }
    tmp = *list;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = elem;
    return 0;
}
