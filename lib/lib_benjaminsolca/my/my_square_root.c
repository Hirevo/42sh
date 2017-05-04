/*
** my_square_root.c for MY_LIB in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:07:02 2017 Benjamin
** Last update Sun Apr  2 20:07:26 2017 Benjamin
*/

#include "bs.h"

int	my_square_root(int nb)
{
  int	i;

  i = 0;
  if (nb < 0)
    {
      my_put_error("WARNING: nb must be unsigned\n");
      return (-1);
    }
  else
    {
      while (i < nb)
	{
	  if (my_power_rec(i, 2) == nb)
	    return (i);
	  i += 1;
	}
    }
  return (0);
}
