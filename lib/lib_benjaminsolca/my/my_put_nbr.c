/*
** my_put_nbr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:38:46 2017 Benjamin
** Last update Sun Apr  2 19:43:11 2017 Benjamin
*/

#include "bs.h"

void    my_put_nbr(int nb)
{
  if (nb < 9)
    my_putchar(nb + '0');
  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * (-1);
    }
  if (nb > 9)
    {
      my_put_nbr(nb / 10);
      nb = nb % 10;
      my_putchar(nb + '0');
    }
}
