/*
** my_find_prime_sup.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:46:06 2017 Benjamin
** Last update Sun Apr  2 21:00:47 2017 Benjamin
*/

#include "bs.h"

int	my_find_prime_sup(int nb)
{
  if (nb <= 2)
    return (2);
  if (nb % 2 == 0)
    nb++;
  while (!is_prime(nb))
      nb = nb + 1;
  return (nb);
}
