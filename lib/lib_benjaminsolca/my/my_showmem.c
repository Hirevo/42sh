/*
** my_showmem.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:47:19 2017 Benjamin
** Last update Mon Apr 17 15:36:13 2017 Benjamin
*/

#include "bs.h"

static void	print_show_mem(char* str, int size)
{
  int		i;

  my_putptr_base(str, "0123456789ABCDEF");
  my_putstr(": ");
  i = -1;
  while (++i < size)
    {
      if (str[i] < 16)
	my_putchar('0');
      my_putnbr_base(str[i], "0123456789ABCDEF");
      if (i % 2 == 1)
	my_putchar(' ');
    }
  i = -1;
  while (++i < size)
    {
      if (is_printable(str[i]))
	my_putchar(str[i]);
      else
	my_putchar('.');
    }
  my_putchar('\n');
}

void	my_showmem(char *str, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    {
      print_show_mem(str, 16);
      str += 16;
    }
}
