/*
** indexof.c for indexof in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 26 00:10:23 2017 Arthur Knoepflin
** Last update Wed Apr 26 00:12:18 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

int	indexof(char **list, char *name)
{
  int	i;

  i = 0;
  while (list[i])
    {
      if (!my_strncmp(list[i], name, my_strlen(name)) &&
	  list[i][my_strlen(name)] == '=')
	return (i);
      i += 1;
    }
  return (-1);
}
