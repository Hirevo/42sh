/*
** my_put_error.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 18:29:58 2017 Benjamin
** Last update Sun Apr  2 19:40:49 2017 Benjamin
*/

#include <unistd.h>
#include "bs.h"

void	my_put_error(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      write(2, &str[i], 1);
      i++;
    }
  return ;
}
