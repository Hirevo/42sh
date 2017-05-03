/*
** my_putchar.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:39:06 2017 Benjamin
** Last update Sun Apr  2 19:40:13 2017 Benjamin
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}
