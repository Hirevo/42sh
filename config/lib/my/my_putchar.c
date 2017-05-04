/*
** my_putchar.c for my_putchar in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:52:11 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:52:12 2017 Arthur Knoepflin
*/

#include <unistd.h>

void	my_putchar_printf(char c, int *count)
{
  *count += 1;
  write(1, &c , 1);
}

void	my_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
}

void	my_putchar(char c)
{
  write(1, &c , 1);
}
