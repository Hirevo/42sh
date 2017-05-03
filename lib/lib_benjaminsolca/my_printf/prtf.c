/*
** main.c for my_printf in /home/prodjia/delivery/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Mon Nov  7 14:51:56 2016 Benjamin
** Last update Wed Apr  5 14:43:18 2017 Benjamin
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "my_prtf.h"

void	tab_fonc_pf(int i, va_list ap, int *count)
{
  void (*tab[12])(va_list, int *count);

  tab[0] = &the_c_pf;
  tab[1] = &the_s_pf;
  tab[2] = &the_i_d_pf;
  tab[3] = &the_i_d_pf;
  tab[4] = &the_x_pf;
  tab[5] = &the_big_x_pf;
  tab[6] = &the_o_pf;
  tab[7] = &the_u_pf;
  tab[8] = &the_b_pf;
  tab[9] = &the_s_oct_pf;
  tab[10] = &the_p_pf;
  tab[11] = NULL;

  tab[i](ap, count);
}

int		my_printf(char *str, ...)
{
  va_list	ap;
  int		i;
  int		count;

  i = -1;
  va_start(ap, str);
  count = 0;
  while (str[++i] != '\0')
    {
      if (str[i] == '%' && str[i++ + 1] != '%')
	{
	  if (str[i] == '\0')
	    return (count);
	  if (check_int_pf(str[i]) != 42)
	    tab_fonc_pf(check_int_pf(str[i]), ap, &count);
	  if (check_int_pf(str[i]) == 42)
	    my_putchar_pf(str[--i], &count);
	}
      else if (str[i] == '%' && str[i + 1] == '%')
	  my_putchar_pf(str[i++], &count);
      else
	my_putchar_pf(str[i], &count);
    }
  va_end(ap);
  return (count);
}
