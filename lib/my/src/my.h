/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** my
*/

#pragma once

#include <stdarg.h>

#define FREE_NONE 0
#define FREE_LEFT 1
#define FREE_BOTH 2
#define FREE_RIGHT 3

typedef struct flags_s {
    char format;
    char length;
    char hold;
    int width;
    int precision;
    char *backup;
} flags_t;

int is_a_num(char *);
void *my_memset(void *, int, int);
int my_puterror(char *);
void my_putchar(char);
void my_isneg(int);
void my_put_nbr(int);
void my_swap(int, int);
void my_putstr(char *);
int my_strlen(char *);
int my_strstrlen(char *, char *);
int my_getnbr(char *);
int *my_sort_int_tab(int *, int);
int my_power_rec(int, int);
int my_square_root(int);
int my_is_prime(int);
int my_find_prime_sup(int);
char *my_strcpy(char *, char *);
char *my_strncpy(char *, char *, int);
char *my_revstr(char *);
char *my_strstr(char *, char *);
int my_strcmp(char *, char *);
int my_strncmp(char *, char *, int);
char *my_strupcase(char *);
char *my_strlowcase(char *);
char *my_strcapitalize(char *);
int my_str_isalpha(char *);
int my_str_isnum(char *);
int my_str_islower(char *);
int my_str_isupper(char *);
int my_str_isprintable(char *);
int my_showstr(char *);
int my_showmem(char *, int);
char *my_strcat(char *, char *);
char *my_strcatdup(char *, char *);
char *my_fstrcat(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strdup(char *);
int my_strlen_until(char *, char);
char *my_strdup_until(char *, char);
int my_strlen_until_x(char *, char, int);
char *my_strdup_until_x(char *, char, int);
char *my_strndup(char *, int);
char **my_strarrdup(char **);
void my_display2(double, int, int, int);
void my_loop(double, int, int, int);
int my_compare1(char *, char *);
int my_compare(char *, char *, int);
int my_printf(char *, ...);
void print_flag(flags_t *, va_list, int *);
flags_t *inititalize_flags(flags_t **, int *);
char *geflags_t(char *, flags_t *, va_list, int *);
void my_octal_putstr(char *, int *, flags_t *);
void my_put_nbr_base(int, int, flags_t *, int *);
void my_put_nbr_long(long, int *);
void my_put_nbr_unsigned(unsigned int, int *);
void my_putchar_printf(char, int *);
void my_putstr_printf(char *, int *, flags_t *, int);
void my_putchar_fd(char, int);
char *my_int_to_char(int);
char *my_unsigned_to_char(unsigned int);
char *my_long_to_char(long);
int nb_args(char **);
void display_pointer(flags_t *, va_list, int *);
void display_number(flags_t *, va_list, char *, int *);
char *complete_str(char *, flags_t *, int *, int);
char *convert_base(char *, char *, char *);
char *check_parse(char *, flags_t *, int *);
int size_nb(int);
