/*
** my_the_fonc.c for my_the_fonc in /home/prodjia/Dropbox/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Tue Nov 15 14:34:33 2016 Benjamin
** Last update Wed Apr  5 14:40:49 2017 Benjamin
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "my_prtf.h"

void	the_c_pf(va_list ap, int *count)
{
  my_putchar_pf(va_arg(ap, int), count);
}

void	the_s_pf(va_list ap, int *count)
{
  my_putstr_pf(va_arg(ap, char *), count);
}

void	the_i_d_pf(va_list ap, int *count)
{
  my_put_nbr_pf(va_arg(ap, int), count);
}

void	the_x_pf(va_list ap, int *count)
{
  my_putnbr_base_pf(va_arg(ap, int), "0123456789abcdef", count);
}

void	the_big_x_pf(va_list ap, int *count)
{
  my_putnbr_base_pf(va_arg(ap, int), "0123456789ABCDEF", count);
}
