/*
** my_fonc.c for my_fonc in /home/prodjia/delivery/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Tue Nov  8 21:48:08 2016 Benjamin
** Last update Thu Apr  6 09:07:52 2017 Benjamin
*/

#include <unistd.h>
#include <stdarg.h>
#include "my_prtf.h"

void	my_putchar_pf(char c, int *count)
{
  (*count)++;
  write(1, &c, 1);
}

void	my_putstr_pf(char *str, int *count)
{
  while (*str != '\0')
    {
      my_putchar_pf(*str, count);
      str = str + 1;
    }
}

void	my_put_nbr_pf(int nb, int *count)
{
  if (nb < 0)
    {
      my_putchar_pf('-', count);
      nb = nb * (-1);
    }
  if (nb <= 9)
    {
      my_putchar_pf(nb + '0', count);
    }
  if (nb > 9)
    {
      my_put_nbr_pf(nb / 10, count);
      nb = nb % 10;
      my_putchar_pf(nb + '0', count);
    }
}

void	my_put_nbr_u_pf(unsigned int nb, int *count)
{
  if (nb <= 9)
    {
      my_putchar_pf(nb + '0', count);
    }
  if (nb > 9)
    {
      my_put_nbr_pf(nb / 10, count);
      nb = nb % 10;
      my_putchar_pf(nb + '0', count);
    }
}

void	my_put_nbr_long_pf(long nb, int *count)
{
  if (nb < 0)
    {
      my_putchar_pf('-', count);
      nb = nb * (-1);
    }
  if (nb <= 9)
    {
      my_putchar_pf(nb + '0', count);
    }
  if (nb > 9)
    {
      my_put_nbr_pf(nb / 10, count);
      nb = nb % 10;
      my_putchar_pf(nb + '0', count);
    }
}
