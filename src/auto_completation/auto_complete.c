/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** auto_complete
*/

#include "auto_complete.h"
#include "my.h"
#include "prompt.h"
#include "shell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int find_matches(match_t **list, char *path, char *str, auto_t *t)
{
    struct dirent **namelist;
    int n;
    int size = scandir(path, &namelist, &filter, &alphasort);
    char *name;
    char *str2;

    if (size <= 0)
        return 0;
    if (size == 1 && strcmp(namelist[0]->d_name, str) == 0)
        return -1;
    n = size;
    str2 = my_strcatdup(str, "*");
    while (--n >= 0)
        if (match(namelist[n]->d_name, str2) == 1) {
            name = strdup(namelist[n]->d_name);
            if (namelist[n]->d_type == DT_DIR)
                name = my_fstrcat(name, "/", 1);
            if (add_in_autolist(list, name) == -1)
                return -1;
            t->is_a_dir = (namelist[n]->d_type == DT_DIR) ? (1) : (0);
        }
    my_free_dirent(namelist, size);
    return 0;
}

int modify_path(auto_t *token, char **path)
{
    int i = 0;
    char *str;

    if (find_a_path(path, token) == -1)
        return -1;
    if (token->is_path == 1)
        return 0;
    if (token->pre_token[0] == 0)
        return 0;
    str = token->pre_token;
    while (str[i])
        i++;
    while (i >= 0 && str[i] == ' ')
        i--;
    if (str[i] == ';')
        return 0;
    *path = ".";
    return 0;
}

char *delete_str(char *to_del, char *content)
{
    int i = 0;
    int m;
    char *str;

    if (strlen(to_del) > strlen(content))
        return to_del;
    while (to_del && to_del[i] && content[i] && to_del[i] == content[i])
        i++;
    str = calloc(strlen(content) - i + 2, sizeof(char));
    if (str == NULL)
        return NULL;
    m = 0;
    while (content && content[i])
        str[m++] = content[i++];
    str[m] = 0;
    return str;
}

static void reprint_and_free(shell_t *shell, match_t **list, auto_t *t)
{
    char *s = t->token ? strdup(t->token) : NULL;

    if (*list) {
        transform(shell, t, list, &s);
        if (shell->is_comp > 0) {
            show_autolist(shell, *list);
            print_prompt(shell);
            if (shell->line)
                printf("%s", shell->line);
        }
        if (strcmp(s, t->token) != 0)
            printf("%s", s);
    }
    shell->is_comp++;
    destroy_the_list(list);
    free(s);
    free(t->token);
    fflush(stdout);
}

int auto_complete(shell_t *shell, char *path)
{
    char **parsed;
    int i;
    int err;
    auto_t token;
    match_t *list;

    if (find_token(shell, &token) == -1)
        return -1;
    token.is_path = 0;
    modify_path(&token, &path);
    if (!path)
        return -1;
    parsed = split_it(path, ":");
    if (!parsed)
        return -1;
    list = NULL;
    i = 0;
    err = 0;
    while (parsed[i] && err != 1) {
        err = find_matches(&list, parsed[i++], token.token, &token);
        if (err == -1)
            return -1;
    }
    if (for_bi(&list, token.token, &token) == -1)
        return -1;
    reprint_and_free(shell, &list, &token);
    my_free_tab((void **)parsed);
    free(token.pre_token);
    free(token.post_token);
    return 0;
}
