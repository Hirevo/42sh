/*
** free_tab.c for my_lib in /home/benjamin/Dropbox/func/free_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 21:34:50 2017 Benjamin
** Last update Mon Apr  3 21:35:58 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"

void	my_free_tab(char **tab)
{
  int   i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}
