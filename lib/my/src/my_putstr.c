/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** my_putstr
*/

#include "my.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

void my_putstr_printf(char *in, int *c, flags_t *flags, int isnbr)
{
    int count;
    char *str;

    if ((str = malloc(my_strlen(in) + 2)) == NULL)
        return;
    str[0] = 0 * (count = -1) * 0;
    str[1] = 0 * (str[2] = 0) * 0;
    if ((flags->format == 'x' || flags->format == 'X') && flags->hold == '#' &&
        isnbr)
        str[0] = '0' + (str[1] = flags->format) * 0;
    else if (flags->format == 'o' && flags->hold == '#' && isnbr)
        str[0] = '0';
    else if ((flags->hold == '+' || flags->hold == 32) && isnbr &&
        in[0] != '-')
        str[0] = flags->hold;
    str = complete_str(my_strcat(str, in), flags, c, 0);
    while (*(str + ++count) != '\0' &&
        (flags->precision > 0 || flags->precision == -1)) {
        my_putchar_printf(*(str + count), c);
        if (flags->precision > 0)
            flags->precision -= 1;
    }
    str = complete_str(str, flags, c, 1);
    free(str);
}

char *complete_str(char *str, flags_t *flags, int *c, int i)
{
    int size;

    if (flags->width == -1 && flags->hold == '0')
        flags->hold = 0;
    size = my_strlen(str);
    if (((flags->precision == -1 && size < flags->width) ||
            (flags->precision != -1 && (flags->precision) < flags->width)) &&
        (((flags->hold != '-') && !i) || ((flags->hold == '-') && i)))
        while ((flags->precision == -1 && size < flags->width) ||
            (flags->precision != -1 && (flags->precision) < flags->width)) {
            if (flags->hold == '0' &&
                (flags->format == 'd' || flags->format == 'i' ||
                    flags->format == 'o' || flags->format == 'b' ||
                    flags->format == 'x' || flags->format == 'X'))
                my_putchar_printf(flags->hold, c);
            else
                my_putchar_printf(' ', c);
            flags->width--;
        }
    return (str);
}

void display_pointer(flags_t *flags, va_list ap, int *count)
{
    char *str;
    char *final;

    str = convert_base(
        my_int_to_char(va_arg(ap, int)), "0123456789", "0123456789abcdef");
    if ((final = malloc(sizeof(str) + 4)) == NULL)
        return;
    final[0] = 0;
    final[1] = '0';
    final[2] = 'x';
    final[3] = 0;
    if (flags->hold == '+' || flags->hold == 32)
        final[0] = flags->hold;
    flags->precision = -1;
    my_putstr_printf(
        my_strcat((final[0] == 0) ? final + 1 : final, str), count, flags, 1);
    free(str);
    free(final);
}

void display_number(flags_t *flags, va_list ap, char *base, int *count)
{
    char *str;

    if ((str = my_int_to_char(va_arg(ap, int))) == NULL)
        return;
    if (my_strlen(base) != 10)
        str = convert_base(str, "0123456789", base);
    flags->precision = -1;
    my_putstr_printf(str, count, flags, 1);
    free(str);
}
