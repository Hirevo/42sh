/*
** my_epur_str.c for lib_my in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Tue Apr  4 17:48:20 2017 Benjamin
** Last update Thu Apr  6 08:35:23 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"

char	*my_epur_str(char *str)
{
  char	*tmp;
  int	i;
  int	k;

  i = 0;
  k = 0;
  if (!(tmp = malloc(sizeof(*tmp) * (my_strlen(str) + 1))))
    return (NULL);
  while ((str[i] == ' ') || (str[i] == '\t'))
    i++;
  while (str[i] != '\0')
    {
      tmp[k++] = str[i++];
      while ((str[i] == ' ') || (str[i] == '\t'))
	i++;
      if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) && (str[i] != '\0'))
	{
	  tmp[k] = ' ';
	  k++;
	}
    }
  tmp[k] = '\0';
  return (tmp);
}
