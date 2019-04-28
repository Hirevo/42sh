/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_printf
*/

#include "my.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_octal_putstr(char *str, int *c, flags_t *flags)
{
    int count;

    count = -1;
    while (str[++count] != 0 &&
        (flags->precision > 0 || flags->precision == -1)) {
        if (str[count] >= 32 && str[count] < 127)
            my_putchar_printf(str[count], c);
        else {
            my_putchar_printf('\\', c);
            my_putchar_printf('0', c);
            if (str[count] <= 7)
                my_putchar_printf('0', c);
            my_put_nbr_base(str[count], 8, flags, c);
        }
        if (flags->precision > 0)
            flags->precision -= 1;
    }
}

void print_nbr(flags_t *flags, va_list ap, int *count)
{
    if (flags->format == 'o')
        display_number(flags, ap, "01234567", count);
    else if (flags->format == 'x' || flags->format == 'X')
        display_number(flags, ap,
            (flags->format == 'x' ? "0123456789abcdef" : "0123456789ABCDEF"),
            count);
    else if (flags->format == 'b')
        display_number(flags, ap, "01", count);
    else if (flags->format == 'u') {
        flags->precision = -1;
        my_putstr_printf(
            my_unsigned_to_char(va_arg(ap, unsigned int)), count, flags, 1);
    } else if (flags->format == 'p')
        display_pointer(flags, ap, count);
    else if (flags->length == 'l' &&
        (flags->format == 'd' || flags->format == 'i'))
        my_putstr_printf(my_long_to_char(va_arg(ap, long)), count, flags, 1);
    else if (flags->format == 'd' || flags->format == 'i')
        display_number(flags, ap, "0123456789", count);
}

void print_flag(flags_t *flags, va_list ap, int *count)
{
    if (flags->format == 's')
        my_putstr_printf(va_arg(ap, char *), count, flags, 0);
    else if (flags->format == 'S')
        my_octal_putstr(va_arg(ap, char *), count, flags);
    else if (flags->format == 'c')
        my_putchar_printf(va_arg(ap, int), count);
    else if (flags->format == '%')
        my_putchar_printf('%', count);
}

void initialize_flags(flags_t *flags, int *count)
{
    *count = 0;
    flags->width = 0;
    flags->precision = 0;
    flags->length = 0;
    flags->format = 0;
    flags->hold = 0;
}

int my_printf(char *str, ...)
{
    int count;
    va_list ap;
    flags_t flags;

    initialize_flags(&flags, &count);
    va_start(ap, str);
    while (*str != 0) {
        if (*str == '%') {
            flags.backup = str;
            str = geflags_t(str + 1, &flags, ap, &count);
            if (flags.format == 'd' || flags.format == 'i' ||
                flags.format == 'p' || flags.format == 'X' ||
                flags.format == 'x' || flags.format == 'o' ||
                flags.format == 'u' || flags.format == 'b')
                print_nbr(&flags, ap, &count);
            else
                print_flag(&flags, ap, &count);
        } else
            my_putchar_printf(*str, &count);
        str += 1;
    }
    va_end(ap);
    return (count);
}
