/*
** my_revstr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:41:12 2017 Benjamin
** Last update Sun Apr  2 20:57:37 2017 Benjamin
*/

#include "bs.h"

char	*my_revstr(char *str)
{
  int	i;
  int	j;
  char	temp;

  j = my_strlen(str) - 1;
  i = 0;
  while (j > i)
    {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i = i + 1;
      j = j - 1;
    }
  return (str);
}
