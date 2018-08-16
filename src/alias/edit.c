/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** edit
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

int insert_alias(shell_t *shell, alias_t *e, int *len, int i)
{
    char *replace;

    len[1] = strlen(shell->line) - len[0] + strlen(e->command);
    replace = calloc(len[1] + 1, sizeof(char));
    if (replace == NULL)
        handle_error("calloc");
    strncpy(replace, shell->line, i);
    strcat(replace, e->command);
    strcat(replace, shell->line + i + len[0]);
    free(shell->line);
    shell->line = replace;
    return 0;
}

static int replace(char *last, int len[2], char *line, int *i)
{
    free(last);
    *i += (len[0] - 1);
    free(line);
    return 0;
}

int check_alias(shell_t *shell, int *i, char *last)
{
    int len[2];
    char *line;
    alias_t found;

    len[0] = my_strstrlen(shell->line + *i, " \t><;|");
    line = my_strndup(shell->line + *i, len[0]);
    for (ssize_t j = 0; j < (ssize_t)(shell->alias->size); j++) {
        char *name = shell->alias->key_table->arr[j];
        if (lstr_equals(line, name)) {
            found.alias = name;
            found.command = shell->alias->value_table->arr[j];
            if (detect_loop(shell, line, *i) == -1 ||
                insert_alias(shell, &found, len, *i) == -1)
                return -1;
            free(last);
            last = line;
            len[0] = my_strstrlen(shell->line + *i, " \t><;|");
            line = my_strndup(shell->line + *i, len[0]);
            if (lstr_equals(line, last))
                break;
            j = -1;
        }
    }
    return replace(last, len, line, i);
}

int parse_alias(shell_t *shell)
{
    int i = -1;
    char *last = 0;
    int c = 1;

    memset(&shell->subst, 0, sizeof(subst_t));
    while (shell->line[++i])
        if (shell->line[i] == '\\')
            i += !!(shell->line[i + 1]);
        else if (is_space(shell->line[i]) || is_separator(shell->line[i])) {
            while (shell->line[i] &&
                (is_space(shell->line[i]) || is_separator(shell->line[i])))
                if (is_delimiter(shell->line[i++]))
                    c = 1;
            i -= 1;
        }
        else if (c && !(c = 0))
            if (check_alias(shell, &i, last) == -1)
                return -1;
    free_subst(shell);
    return 0;
}
