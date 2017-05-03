/*
** my_strstr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:41:38 2017 Benjamin
** Last update Sun Apr  2 21:00:30 2017 Benjamin
*/

#include "bs.h"

char	*my_strstr(char *str, char *to_find)
{
  int	i;
  int	j;
  int	memo;

  i = 0;
  j = 0;
  memo = 0;
  if (to_find[0] == '\0')
    return (str);
  while  (str[i] && to_find[j])
    {
      if (str[i] == to_find[j])
	{
	  if (j == 0)
	    memo = i;
	  j++;
	}
      else
	j = 0;
      i++;
      if (to_find[j] == '\0')
	return (&str[memo]);
    }
  return (NULL);
}
