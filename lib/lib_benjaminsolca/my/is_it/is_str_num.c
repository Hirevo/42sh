/*
** is_str_num.c for mylib in /home/benjamin/Dropbox/dante/lib/lib_benjaminsolca/my/is_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Tue Apr 25 10:06:03 2017 Benjamin
** Last update Tue Apr 25 10:20:32 2017 Benjamin
*/

#include "bs.h"

int	is_str_num(char *str)
{
  int	i;

  i = -1;
  if (str[0] == '-')
    i++;
  while (str[++i] != '\0')
    {
      if (is_num(str[i]) != 1)
	return (1);
    }
  return (0);
}
