/*
** is_str_char.c for my_lib in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/is_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Thu Apr  6 15:35:34 2017 Benjamin
** Last update Tue Apr 25 10:01:50 2017 Benjamin
*/

#include "bs.h"

int	is_str_char(char *str, char c)
{
  int	i;

  i = -1;
  while (str[++i] != '\0')
    {
      if (str[i] == c)
	return (1);
    }
  return (0);
}
