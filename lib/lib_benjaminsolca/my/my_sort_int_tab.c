/*
** my_sort_int_tab.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:01:14 2017 Benjamin
** Last update Sun Apr  2 20:37:18 2017 Benjamin
*/

void	my_sort_int_tab(int* tab, int size)
{
  int	i;
  int	j;
  int	min;
  int	tmp;

  i = 0;
  j = 0;
  min = 0;
  while (i < size)
    {
      while (j < size)
	{
	  if (tab[j] < tab[min])
	    min = j;
	  j++;
	}
      tmp = tab[i];
      tab[i] = tab[min];
      tab[min] = tmp;
      i++;
      j = i;
      min = i;
    }
}
