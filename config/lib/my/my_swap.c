/*
** my_swap.c for my_swap in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:02:53 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:02:54 2017 Arthur Knoepflin
*/

int	my_swap(int *a, int *b)
{
  int	temp;

  temp = *a;
  *a = *b;
  *b = temp;
}
