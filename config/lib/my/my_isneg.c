/*
** my_isneg.c for my_isneg in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:44:37 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:44:39 2017 Arthur Knoepflin
*/

#include "my.h"

int	my_isneg(int n)
{
  if (n < 0)
    my_putchar('N');
  else
    my_putchar('P');
}
