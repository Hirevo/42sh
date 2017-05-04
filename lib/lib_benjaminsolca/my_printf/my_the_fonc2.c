/*
** my_the_fonc2.c for my_the_fonc2 in /home/prodjia/Dropbox/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Tue Nov 15 15:26:21 2016 Benjamin
** Last update Wed Apr  5 14:41:05 2017 Benjamin
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "my_prtf.h"

void	the_o_pf(va_list ap, int *count)
{
  my_putnbr_base_pf(va_arg(ap, int), "01234567", count);
}

void	the_u_pf(va_list ap, int *count)
{
  my_put_nbr_u_pf(va_arg(ap, int), count);
}

void	the_b_pf(va_list ap, int *count)
{
  my_putnbr_base_pf(va_arg(ap, int), "01", count);
}

void	the_s_oct_pf(va_list ap, int *count)
{
  my_putstr_oct_pf(va_arg(ap, char *), count);
}
