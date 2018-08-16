/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** history
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int insert_one_hist(shell_t *shell, int i, int n)
{
    int len = -1;
    char **last = lvec_back(shell->hist.arr);
    char *str;

    if (last == 0)
        return -1;
    while (last && last[++len])
        ;
    if (n >= len)
        return ret_error(shell, "Bad ! arg selector.\n");
    len = strlen(last[n]) + strlen(shell->line);
    len += strlen(shell->line) - 3;
    str = calloc(len + 1, sizeof(char));
    if (str == NULL)
        return -1;
    strncpy(str, shell->line, i);
    strcat(str, last[n]);
    strcat(str, shell->line + i + 3);
    free(shell->line);
    shell->line = str;
    return 0;
}

static int insert_full_hist(shell_t *shell, int i)
{
    int len = 0;
    int l = -1;
    char *str;
    char **last = lvec_back(shell->hist.arr);

    if (last == 0)
        return -1;
    while (last[++l])
        len += strlen(last[l]);
    len += strlen(shell->line) - 2 + l;
    str = calloc(len + 1, sizeof(char));
    if (str == NULL)
        return -1;
    strncpy(str, shell->line, i);
    l = -1;
    while (last[++l])
        strcat(l ? strcat(str, " ") : str, last[l]);
    strcat(str, shell->line + i + 2);
    free(shell->line);
    shell->line = str;
    return 0;
}

static int insert_last_hist(shell_t *shell, int i)
{
    int len = 0;
    int l = -1;
    char *str;
    char **last = lvec_back(shell->hist.arr);

    if (last == 0)
        return -1;
    while (last[++l])
        ;
    l -= 1;
    len = strlen(last[l]);
    len += strlen(shell->line) - 2;
    str = calloc(len + 1, sizeof(char));
    if (str == NULL)
        return -1;
    strncpy(str, shell->line, i);
    strcat(str, last[l]);
    strcat(str, shell->line + i + 2);
    free(shell->line);
    shell->line = str;
    return 0;
}

static void final_things(shell_t *shell, char *last, int save)
{
    char *str;
    char **l = lvec_back(shell->hist.arr);

    str = NULL;
    if (l != NULL)
        str = construct_alias(l);
    if (last != shell->line)
        printf("%s\n", shell->line);
    if (save && strcmp(shell->line, "exit") &&
        (l == NULL || (strcmp(str, shell->line))))
        add_hist_elem(shell, shell->line);
    free(str);
}

static int is_hist_sym(shell_t *shell, int i)
{
    if (my_strncmp(shell->line + i, "!!", 2) == 0) {
        if (insert_full_hist(shell, i) == -1)
            return -1;
    }
    else if (my_strncmp(shell->line + i, "!$", 2) == 0) {
        if (insert_last_hist(shell, i) == -1)
            return -1;
    }
    else if (my_strncmp(shell->line + i, "!:", 2) == 0 &&
        (shell->line[i + 2] >= '0' && shell->line[i + 2] <= '9'))
        if (insert_one_hist(shell, i, shell->line[i + 2] - '0') == -1)
            return -1;
    return 0;
}

int parse_history(shell_t *shell, int save)
{
    int i;
    char *last;
    int quoted = 0;

    i = -1;
    last = shell->line;
    while (lvec_back(shell->hist.arr) && shell->line[++i])
        if (shell->line[i] == '\\')
            i += !!(shell->line[i + 1]);
        else if (shell->line[i] == '\'')
            quoted = !quoted;
        else if (!quoted)
            if (is_hist_sym(shell, i) == -1)
                return -1;
    final_things(shell, last, save);
    return 0;
}
