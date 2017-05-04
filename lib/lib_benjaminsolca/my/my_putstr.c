/*
** my_putstr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:39:44 2017 Benjamin
** Last update Thu Apr  6 08:53:04 2017 Benjamin
*/

#include "bs.h"

int	my_putstr(char *str)
{

  while (*str != '\0')
    {
      my_putchar(*str);
      str = str + 1;
    }
  return (0);
}
