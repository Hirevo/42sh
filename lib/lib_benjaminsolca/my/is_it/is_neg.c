/*
** is_neg.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:37:04 2017 Benjamin
** Last update Thu Apr  6 08:50:11 2017 Benjamin
*/

#include "bs.h"

int	is_neg(int n)
{
  char	positif;
  char	neg_or_null;

  positif = 'P';
  neg_or_null = 'N';
  if (n >= 0)
    my_putchar(positif);
  else
    my_putchar(neg_or_null);
  return (0);
}
