/*
** my_sort_int_table.c for my_sort_int_table in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:55:30 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:55:31 2017 Arthur Knoepflin
*/

#include "my.h"

int	*my_sort_int_tab(int *tab, int size)
{
  int	trouble;
  int	i;

  trouble = 1;
  while (trouble)
    {
      i = 0;
      trouble = 0;
      while (i < size)
	{
	  if (tab[i] > tab[i + 1])
	    {
	      my_swap(tab[i], tab[i + 1]);
	      trouble = 1;
	    }
	  i = i + 1;
	}
    }
  return (tab);
}
