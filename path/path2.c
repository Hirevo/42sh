/*
** path2.c for minishell1 in /home/nicolaspolomack/shell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan 16 00:57:24 2017 Nicolas Polomack
** Last update Mon Jan 16 01:01:43 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"

char	**set_default_path()
{
  char	**path;

  if ((path = malloc(8 * 3)) == NULL ||
      (path[0] = my_strdup("/bin")) == NULL ||
      (path[1] = my_strdup("/usr/bin")) == NULL)
    return (NULL);
  path[2] = NULL;
  return (path);
}
