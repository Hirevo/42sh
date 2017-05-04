/*
** my_strstr.c for my_strstr in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:02:30 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:02:31 2017 Arthur Knoepflin
*/

#include <stdlib.h>

char	*my_strstr(char *str, char *to_find)
{
  int	count;
  int	to_find_count;

  count = 0;
  to_find_count = 0;
  while (*str != '\0')
    {
      while (*(str + count) == *(to_find + to_find_count) &&
	     *(to_find + to_find_count) != '\0')
	{
	  count = count + 1;
	  if (*(to_find + to_find_count + 1) == '\0')
	      return (str);
	  to_find_count = to_find_count + 1;
	}
      str = str + count + 1;
      count = 0;
      to_find_count = 0;
    }
  return (NULL);
}
