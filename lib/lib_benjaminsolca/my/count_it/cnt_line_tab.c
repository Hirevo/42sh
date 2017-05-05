/*
** count_line_tab.c for lib_my in /home/benjamin/Dropbox/PSU_2016_minishell2/lib/my/count_it/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri Apr  7 14:49:03 2017 Benjamin
** Last update Fri Apr  7 14:50:34 2017 Benjamin
*/

#include "bs.h"

int	cnt_line_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i] != NULL);
  return (i);
}
