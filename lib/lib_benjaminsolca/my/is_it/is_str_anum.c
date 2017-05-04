/*
** is_str_anum.c for my_lib in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/is_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Thu Apr  6 15:35:34 2017 Benjamin
** Last update Thu Apr  6 17:41:20 2017 Benjamin
*/

#include "bs.h"

int	is_str_anum(char *str)
{
  int	i;

  i = -1;
  while (str[++i] != '\0')
    {
      if (is_alphanum(str[i]) != 1)
	return (1);
    }
  return (0);
}
