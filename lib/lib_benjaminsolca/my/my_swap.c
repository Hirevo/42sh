/*
** my_swap.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:42:08 2017 Benjamin
** Last update Thu Apr  6 08:53:26 2017 Benjamin
*/

int	my_swap(int *a, int *b)
{
  int	 mem;

  mem = *a;
  *a = *b;
  *b = mem;
  return (0);
}
