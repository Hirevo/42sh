/*
** my_cpy_tab.c for my_lib in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Mon Apr  3 20:04:47 2017 Benjamin
** Last update Thu Apr  6 15:03:01 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"

int	count_line_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i] != NULL);
  return (i);
}

char	**my_cpy_tab(char **to_cpy)
{
  char	**dest;
  int   i;
  int   j;

  i = -1;
  if (!(dest = malloc(sizeof(char *) * (count_line_tab(to_cpy) + 1))))
    return (NULL);
  while (to_cpy[++i] != NULL)
    {
      j = -1;
      if (!(dest[i] = malloc(sizeof(char)
			     * (my_strlen(to_cpy[i]) + 1))))
	return (NULL);
      while (to_cpy[i][++j] != '\0')
	dest[i][j] = to_cpy[i][j];
      dest[i][j] = '\0';
    }
  dest[i] = NULL;
  return (dest);
}
