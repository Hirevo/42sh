/*
** my_fonc2.c for my_fonc2 in /home/prodjia/delivery/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Wed Nov  9 19:46:02 2016 Benjamin
** Last update Wed Apr  5 14:39:48 2017 Benjamin
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_prtf.h"

void	my_putchar_u_pf(unsigned char c, int *count)
{
  (*count)++;
  write (1, &c, 1);
}

int	my_strlen_pf(char *str)
{
  int	i;

  i = 0;
  while (*str != '\0')
    {
      i = i + 1;
      str = str + 1;
    }
  return (i);
}

int	my_po_pf(int nb, int i)
{
  int   calc;

  calc = nb;
  while (i-- != 1)
    calc = calc * nb;
  return (calc);
}

void	my_putstr_oct_pf(char *str, int *count)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 32 && str[i] < 127)
	my_putchar_pf(str[i], count);
      else
	{
	  my_putchar_pf('\\', count);
	  if (str[i] < 8)
	    {
	      my_putstr_pf("00", count);
	      my_putnbr_base_pf(str[i], "01234567", count);
	    }
	  else if (str[i] > 7 && str[i] < 32)
	    {
	      my_putchar_pf('0', count);
	      my_putnbr_base_pf(str[i], "01234567", count);
	    }
	  else
	    my_putnbr_base_pf(str[i], "01234567", count);
	}
      i++;
    }
}
