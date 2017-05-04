/*
** my_fonc3.c for my_fonc3 in /home/prodjia/Dropbox/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Wed Nov 16 10:29:44 2016 Benjamin
** Last update Wed Apr  5 14:40:29 2017 Benjamin
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_prtf.h"

void				my_pointer_adress_pf(void *ptr, int *count)
{
  unsigned long long int	res;

  res = (unsigned long long int)ptr;
  my_putstr_pf("0x", count);
  my_base_long_pf(res, "0123456789abcdef", count);
}

void		my_putnbr_base_pf(unsigned int nbr, char *base, int *count)
{
  unsigned int  calc;
  int           len;

  calc = nbr;
  len = my_strlen_pf(base);
  if (calc != 0)
    my_putnbr_base_pf(calc / len, base, count);
  if (calc != 0)
    my_putchar_pf(base[calc%len], count);
}

void				my_base_long_pf(unsigned long long int nbr,
					      char *base, int *count)
{
  unsigned long long int	calc;
  int				len;

  calc = nbr;
  len = my_strlen_pf(base);
  if (calc != 0)
    my_base_long_pf(calc / len, base, count);
  if (calc != 0)
    my_putchar_pf(base[calc%len], count);
}
