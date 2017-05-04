/*
** my_getnbr.c for my_getnbr in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:43:53 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:43:55 2017 Arthur Knoepflin
*/

#include "my.h"

int	my_getnbr(char *str)
{
  int	i;
  int	factor;
  int	total;
  int	is_neg;

  factor = 1;
  i = 0;
  total = 0;
  is_neg = 1;
  while (*str == '+' || *str == '-')
    if (*(str++) == '-')
      is_neg *= -1;
  while (str[i] >= '0' && str[i] <= '9')
    i += 1;
  i -= 1;
  while (i >= 0)
    {
      total += (str[i] - '0') * factor;
      factor *= 10;
      i -= 1;
    }
  return (total * is_neg);
}
