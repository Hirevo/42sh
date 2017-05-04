/*
** free_tab.c for free_tab in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Thu Mar 30 15:09:51 2017 Arthur Knoepflin
** Last update Thu Mar 30 15:12:50 2017 Arthur Knoepflin
*/

#include <stdlib.h>

void	free_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i])
    free(tab[i]);
  free(tab);
}
