/*
** my_strdup.c for my_strdup in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:57:24 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:57:27 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *src)
{
  char	*resp;
  int	count;

  count = 0;
  resp = malloc(sizeof(char) * (my_strlen(src) + 1));
  if (resp == NULL)
    return (NULL);
  while (src[count] != '\0')
    {
      resp[count] = src[count];
      count = count + 1;
    }
  resp[count] = '\0';
  return (resp);
}

char	**my_strarrdup(char **arr)
{
  char	**final;
  int	i;

  i = -1;
  while (arr[++i]);
  if ((final = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  i = -1;
  while (arr[++i])
    final[i] = my_strdup(arr[i]);
  final[i] = NULL;
  return (final);
}

