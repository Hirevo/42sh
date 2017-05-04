/*
** my_showstr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:47:52 2017 Benjamin
** Last update Sun Apr  2 20:58:22 2017 Benjamin
*/

#include "bs.h"

void	my_showstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (is_printable(str[i]))
	{
	  my_putchar(str[i]);
	}
      else
	{
	  my_putchar('\\');
	  if (str[i] < 16)
	    {
	      my_putchar('0');
	    }
	  my_putnbr_base(str[i], "0123456789abcdef");
	}
      i++;
    }
}
