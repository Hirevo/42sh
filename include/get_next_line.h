/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** get_next_line
*/

#pragma once

#ifndef READ_SIZE
#define READ_SIZE 4096
#endif /* !READ_SIZE */

char *get_next_line(const int);
int get_line_str(const int, char **, int);
char *get_final_line(char **);
char *my_realloc(char *, char *);
char *line_cases(int, int *, char **);
