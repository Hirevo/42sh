/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** alias
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int add_alias(Shell *shell, char *alias, char *command)
{
    free(lhmap_get(shell->aliases, alias));
    lhmap_set(shell->aliases, alias, strdup(command));
    return 0;
}

int disp_all_alias(Shell *shell)
{
    vec_t *keys;
    vec_t *vals;

    if (shell->aliases == NULL)
        return 0;
    keys = shell->aliases->key_table;
    vals = shell->aliases->value_table;
    for (size_t i = 0; i < shell->aliases->size; i++) {
        const char *name = keys->arr[i];
        const char *command = vals->arr[i];
        printf("alias %s='%s'\n", name, command);
    }
    return 0;
}

int disp_alias(Shell *shell, char *alias)
{
    char *found;

    if (shell->aliases == NULL)
        return 0;
    found = lhmap_get(shell->aliases, alias);
    if (found)
        printf("alias %s='%s'\n", alias, found);
    return 0;
}

char *construct_alias(char **tab)
{
    int i = -1;
    int len = 0;
    char *ret;

    while (tab[++i])
        len += ((!!i) + strlen(tab[i]));
    ret = calloc(len + 1, sizeof(char));
    if (ret == NULL)
        handle_error("calloc");
    *ret = 0;
    i = -1;
    while (tab[++i])
        strcat(i ? strcat(ret, " ") : ret, tab[i]);
    return ret;
}

char *get_alias_cmd(Shell *shell, char *name)
{
    char *found;

    if (shell->aliases == 0 || name == 0)
        return 0;
    found = lhmap_get(shell->aliases, name);
    if (found)
        return strdup(found);
    return 0;
}
