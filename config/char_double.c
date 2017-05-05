/*
** char_double.c for char_double in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 23:55:08 2017 Arthur Knoepflin
** Last update Tue Apr 25 11:33:07 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

char	**add_to_chardouble(char *str, char **list)
{
  int	i;
  char	**ret;

  if ((ret = malloc(sizeof(char *) * (nb_args(list) + 2))) == NULL)
    return (NULL);
  ret[nb_args(list) + 1] = NULL;
  i = 0;
  while (list && list[i])
    {
      ret[i] = my_strdup(list[i]);
      i += 1;
    }
  ret[i] = my_strdup(str);
  return (ret);
}

char	**del_to_chardouble(char *str, char **list)
{
  int	i;
  int	j;
  char	**ret;

  if ((ret = malloc(sizeof(char *) * (nb_args(list)))) == NULL)
    return (NULL);
  ret[nb_args(list) - 1] = NULL;
  i = 0;
  j = 0;
  while (list && list[i])
    {
      if (my_strncmp(list[i], str, my_strlen(str)))
	{
	  ret[j] = my_strdup(list[i]);
	  j += 1;
	}
      i += 1;
    }
  return (ret);
}
