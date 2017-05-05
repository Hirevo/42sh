/*
** my_concat.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 18:25:34 2017 Benjamin
** Last update Sun Apr  2 19:40:20 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"

char	*my_concat(char *str, char *str2)
{
  char	*result;
  int	i;
  int	j;
  int	total;

  if (str2 == NULL)
    return (str);
  total = my_strlen(str) + my_strlen(str2);
  if ((result = malloc(sizeof(char) * (total + 2))) == NULL)
    return (NULL);
  j = 0;
  i = 0;
  while (str[i] != '\0')
    result[j++] = str[i++];
  i = 0;
  while (str2[i] != '\0' && str2[i] != '\n')
    result[j++] = str2[i++];
  result[j] = '\0';
  return (result);
}
