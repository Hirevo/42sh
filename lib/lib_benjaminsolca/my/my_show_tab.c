/*
** my_show_tab.c for my_lib.c in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 18:33:06 2017 Benjamin
** Last update Sun Apr  2 19:47:11 2017 Benjamin
*/

#include "bs.h"

void	my_show_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i])
    {
      my_putstr(tab[i]);
      my_putchar('\n');
    }
}
