/*
** my_put_nbr_base.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 18:31:27 2017 Benjamin
** Last update Thu Apr  6 09:08:14 2017 Benjamin
*/

#include "bs.h"

void	my_convertnbr_base_rec(int nbr, char* base,
			       int base_len, char* str)
{
  if (nbr < 0)
    my_putchar('-');
  else
    nbr = -nbr;
  if (nbr <= -base_len)
    my_convertnbr_base_rec(-(nbr / base_len), base, base_len, str + 1);
  else
    str[1] = '\0';
  *str = base[-(nbr % base_len)];
}

void	my_putnbr_base(int nbr, char *base)
{
  char	str[my_strlen(base)];
  int	len;

  len = my_strlen(base);
  my_convertnbr_base_rec(nbr, base, len, str);
  my_revstr(str);
  my_putstr(str);
}

void	my_putptr_base(void* ptr, char* base)
{
  int	*tab;
  int	nb_put;
  int	i;

  tab = (int*)ptr;
  nb_put = (sizeof(void*)) / (sizeof(int));
  i = -1;
  while (++i < nb_put)
    {
      my_putnbr_base(tab[i], base);
    }
}
