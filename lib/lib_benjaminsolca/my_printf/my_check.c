/*
** check.c for check in /home/prodjia/delivery/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Tue Nov  8 22:42:48 2016 Benjamin
** Last update Thu Apr  6 08:41:17 2017 Benjamin
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "my_prtf.h"

void	my_putchar2_pf(char c)
{
  write(2, &c, 1);
}

void	my_putstr2_pf(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    my_putchar2_pf(str[i++]);
}

void	check_mallc_pf(char *str)
{
  if (str == NULL)
    {
      my_putstr2_pf(ERROR_MSG);
      return ;
    }
}

int	check_int_pf(char c)
{
  int   i;
  char  *str;

  i = 0;
  str = "csidxXoubSp";
  while (str[i] != '\0')
    {
      if (c == str[i])
	return (i);
      i++;
    }
  return (42);
}

int	check_int_flag_pf(char c)
{
  int   i;
  char  *str;

  i = 0;
  str = "#0- +";
  while (str[i] != '\0')
    {
      if (c == str[i])
	return (i);
      i++;
    }
  return (42);
}
