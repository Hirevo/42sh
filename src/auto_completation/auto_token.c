/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** auto_token
*/

#include "auto_complete.h"
#include "my.h"
#include "shell.h"
#include <stdlib.h>

int find_a_path(char **path, auto_t *token)
{
    char *str = token->token;
    int i = strlen(str) - 1;
    char *new;

    while (i >= 0 && str[i] != '/')
        i--;
    if (i == 0 && str[i] != '/')
        return 0;
    else if (i >= 0) {
        new = calloc(strlen(str + i) + 1, sizeof(char));
        if (new == NULL)
            return -1;
        new = strdup(str + i + 1);
        token->token = new;
        *path = strndup(str, i + 1);
        token->pre_token =
            my_strcatdup(token->pre_token, strndup(str, i + 1));
        free(str);
        token->is_path = 1;
    }
    return 1;
}

char *extract_posttoken(char *str, int end)
{
    char *post_token;
    int i = end + 1;
    int m = 0;

    if (end == 0)
        return strdup("");
    if (!str[end + 1])
        return strdup("");
    post_token = calloc(strlen(str) - end, sizeof(char));
    if (post_token == NULL)
        return NULL;
    while (str[i])
        post_token[m++] = str[i++];
    post_token[m] = 0;
    return post_token;
}

char *extract_pretoken(char *str, int start)
{
    char *pre_token = calloc(start + 1, sizeof(char));
    int i = 0;

    if (start == 0)
        return strdup("");
    if (pre_token == NULL)
        return NULL;
    while (i < start) {
        pre_token[i] = str[i];
        i++;
    }
    pre_token[i] = 0;
    return pre_token;
}

char *extract_token(char *str, int i, int *start, int *end)
{
    char *token;
    int m = 0;

    if (str == NULL)
        return strdup("");
    while (i >= 0 && str && str[i] != ' ')
        i--;
    *start = ++i;
    *end = i + word_length(str, i, " ") - 1;
    token = calloc(*end - *start + 2, sizeof(char));
    if (token == NULL)
        return NULL;
    while (i <= *end)
        token[m++] = str[i++];
    token[m] = 0;
    return token;
}

int find_token(shell_t *shell, auto_t *token)
{
    int start = 0;
    int end = 0;

    token->token = extract_token(shell->line, shell->w.cur, &start, &end);
    if (!token->token)
        return -1;
    token->pre_token = extract_pretoken(shell->line, start);
    if (!token->pre_token)
        return -1;
    token->post_token = extract_posttoken(shell->line, end);
    if (!token->post_token)
        return -1;
    return 0;
}
