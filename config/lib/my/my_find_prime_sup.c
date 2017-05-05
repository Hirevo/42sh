/*
** my_find_prime_sup.c for my_find_prime_sup in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:40:42 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:40:45 2017 Arthur Knoepflin
*/

#include "my.h"

int	my_find_prime_sub(int nb)
{
  if (nb <= 0)
    return (2);
  while (my_is_prime(nb) != 1 && nb < 2147483648)
    {
      nb = nb + 1;
      if (nb == 2147483648)
	return (0);
    }
  return (nb);
}
