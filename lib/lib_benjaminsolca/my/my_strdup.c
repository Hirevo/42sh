/*
** my_strdup.c for my_lib in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Tue Apr  4 18:41:33 2017 Benjamin
** Last update Tue Apr  4 22:18:47 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"

char	*my_strdup(char *str)
{
  char	*s;

  if ((s = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  return (my_strcpy(s, str));
}
