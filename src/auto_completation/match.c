/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** match
*/

#include "auto_complete.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>
#include <string.h>

int for_bi(match_t **list, char *str, auto_t *t)
{
    char **bi = get_builtin_tab();
    int i = 0;
    char *str2 = my_strcatdup(str, "*");

    if (t->pre_token[0] != 0)
        return 0;
    while (bi[i]) {
        if (match(bi[i], str2) == 1 &&
            add_in_autolist(list, strdup(bi[i])) == -1)
            return -1;
        i++;
    }
    return 0;
}

int filter(const struct dirent *l)
{
    if ((strcmp((char *)l->d_name, ".")) == 0 ||
        (strcmp((char *)l->d_name, "..")) == 0)
        return 0;
    return 1;
}

static char *find_occurences(match_t **list)
{
    int i = 0;
    char prec = 0;
    int g = 0;
    char *str = 0;
    match_t *tmp = 0;

    while (g == 0) {
        tmp = *list;
        prec = tmp->cmd[i];
        while (tmp && tmp->cmd[i] == prec)
            tmp = tmp->next;
        if (tmp) {
            str = strndup(tmp->cmd, i);
            g = 1;
        }
        i++;
    }
    return str;
}

void transform(shell_t *shell, auto_t *t, match_t **list, char **s)
{
    char *str;

    if ((*list)->next == NULL) {
        str = strdup((*list)->cmd);
        shell->is_comp = 0;
    }
    else
        str = find_occurences(list);
    *s ? free(shell->line) : 0;
    str = sanitize(str, 1);
    shell->line = my_strcatdup(t->pre_token, str);
    shell->line = my_fstrcat(shell->line, t->post_token, 1);
    str = delete_str(*s, str);
    if (t->post_token && (*list)->next == NULL)
        *s = my_strcatdup(str, t->post_token);
    shell->w.cur = strlen(shell->line);
    t->is_a_dir = 0;
}

int match(char *s1, char *s2)
{
    int ret;

    if (*s1 == '\0' && *s2 == '\0')
        return 1;
    else if (*s2 == '*' && *s1 == '\0')
        ret = match(s1, s2 + 1);
    else if (*s2 == '*')
        ret = (match(s1, s2 + 1) || match(s1 + 1, s2));
    else if (*s1 == *s2)
        ret = match(s1 + 1, s2 + 1);
    else
        return 0;
    return ret;
}
