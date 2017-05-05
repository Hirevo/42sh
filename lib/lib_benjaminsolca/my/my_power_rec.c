/*
** my_power_rec.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:38:04 2017 Benjamin
** Last update Sun Apr  2 19:43:23 2017 Benjamin
*/

#include "bs.h"

int	my_power_rec(int nb, int p)
{
  if (p == 0)
    return (1);
  if (p < 0)
    return (0);
  return (nb * my_power_rec(nb, p -1));
}
