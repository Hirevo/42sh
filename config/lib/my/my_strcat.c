/*
** my_strcat.c for my_strcat in /home/arthur/delivery/CPool_Day07
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Oct 11 12:47:24 2016 Arthur Knoepflin
** Last update Tue Jan  3 21:38:07 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"

char	*my_strcat(char *str1, char *str2)
{
  int	i;
  int	j;
  char	*ret;

  ret = malloc(sizeof(*ret) * (my_strlen(str1) + my_strlen(str2) + 1));
  ret[my_strlen(str1) + my_strlen(str2)] = '\0';
  i = 0;
  while (str1[i])
    {
      ret[i] = str1[i];
      i += 1;
    }
  j = 0;
  while (str2[j])
    {
      ret[i] = str2[j];
      i += 1;
      j += 1;
    }
  return (ret);
}
