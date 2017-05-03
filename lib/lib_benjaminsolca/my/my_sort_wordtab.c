/*
** my_sort_wordtab.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:03:47 2017 Benjamin
** Last update Thu Apr  6 08:43:44 2017 Benjamin
*/

#include "bs.h"

void	my_sort_wordtab(char **tab)
{
  int	i;
  int	j;
  char	*memo;

  i = 0;
  while (tab[++i] != '\0')
    {
      if (tab[i] == '\0')
	  i = 1;
      j = i - 1;
      if (my_strcmp(tab[i], tab[j]) < 0)
	{
	  memo = tab[j];
	  tab[j] = tab[i];
	  tab[i] = memo;
	  i = 0;
	}
    }
}
