/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** auto_complete
*/

#pragma once

#include "shell.h"
#include <dirent.h>

typedef struct auto_s {
    char *pre_token;
    char *token;
    char *post_token;
    int is_path;
    int is_a_dir;
} auto_t;

typedef struct match_s {
    char *cmd;
    unsigned char type;
    struct match_s *next;
} match_t;

int auto_complete(shell_t *shell, char *path);
int match(char *s1, char *s2);
char **split_it(char *str, char *to_split);
int word_length(char *str, int i, char *to_split);
void my_free_dirent(struct dirent **tab, int size);
void my_free_tab(void **tab);
int find_a_path(char **path, auto_t *token);
void transform(shell_t *shell, auto_t *t, match_t **list, char **s);
char *delete_str(char *to_del, char *content);
int for_bi(match_t **list, char *str2, auto_t *t);
char **get_builtin_tab();
int filter(const struct dirent *l);

/*
** List
*/

int add_in_autolist(match_t **list, char *cmd);
void show_autolist(shell_t *, match_t *);
void destroy_the_list(match_t **list);

/*
** Tokens
*/

int find_token(shell_t *shell, auto_t *token);
