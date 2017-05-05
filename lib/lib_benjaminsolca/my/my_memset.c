/*
** my_memset.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:37:33 2017 Benjamin
** Last update Sun Apr  2 20:51:54 2017 Benjamin
*/

#include "stdio.h"

void		*my_memset(void *toset, int tobeset, size_t size)
{
  unsigned int	i;

  i = 0;
  while (i < size)
    {
      ((char *)toset)[i] = tobeset;
      i++;
    }
  return (toset);
}
