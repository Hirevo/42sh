/*
** my_put_nbr.c for my_put_nbr in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:53:13 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:53:15 2017 Arthur Knoepflin
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

void	my_put_nbr_base(int n, int base, t_flags *flags, int *count)
{
  int	nbr;

  if (n < 0)
    {
      my_putchar_printf('-', count);
      n *= -1;
    }
  if (n >= 0)
    {
      if (n >= base)
	{
	  nbr = (n % base);
	  n = (n - nbr) / base;
	  my_put_nbr_base(n, base, flags, count);
	  if (nbr < 10)
	    my_putchar_printf('0' + n, count);
	  else
	    my_putchar_printf((flags->format == 'X' ? 'A' : 'a') + n - 10, count);
	}
    }
  else
    if (n < 10)
      my_putchar_printf('0' + n, count);
    else
      my_putchar_printf((flags->format == 'X' ? 'A' : 'a') + n - 10, count);
}

void	my_put_nbr(int n)
{
  int	nbr;

  if (n < 0)
    {
      my_putchar('-');
      n *= -1;
    }
  if (n >= 0)
    {
      if (n >= 10)
	{
	  nbr = (n % 10);
	  n = (n - nbr) / 10;
	  my_put_nbr(n);
	  my_putchar('0' + nbr);
	}
      else
	my_putchar('0' + n);
    }
  else
    my_putchar('0' + n);
}

char	*my_long_to_char(long i)
{
  char	*resp;
  char	isNegative;
  long	n;
  long	size;

  (i < 0) ? isNegative = '-' + ((i *= -1) * 0) : 0;
  n = i;
  size = 0;
  while (n > 0)
    n /= 10 + ((size += 1) * 0);
  size += 2;
  if ((resp = malloc(sizeof(char) * size + 1)) == NULL)
    return (NULL);
  resp[size--] = 0;
  if (i == 0)
    resp[size--] = '0';
  else
    while (i > 0)
      {
	resp[size--] = i % 10 + '0';
	i /= 10;
      }
  (isNegative == '-') ? resp[size--] = isNegative : 0;
  return (resp + size + 1);
}
