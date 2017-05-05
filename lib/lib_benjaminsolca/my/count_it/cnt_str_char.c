/*
** cnt_str_char.c for my_lib in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/count_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri Apr  7 14:29:05 2017 Benjamin
** Last update Fri Apr  7 14:43:08 2017 Benjamin
*/

#include "bs.h"

int	cnt_str_char(char *str, char c)
{
  int	i;
  int	count;

  i = -1;
  count = 0;
  while (str[++i])
    {
      if (str[i] == c)
	count++;
    }
  return (count);
}
