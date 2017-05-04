/*
** my_the_fonc3.c for my_the_fonc3 in /home/prodjia/Dropbox/PSU_2016_my_printf
**
** Made by Benjamin
** Login   <prodjia@epitech.net>
**
** Started on  Wed Nov 16 10:02:39 2016 Benjamin
** Last update Thu Apr  6 10:47:58 2017 Benjamin
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "my_prtf.h"

void	the_p_pf(va_list ap, int *count)
{
  my_pointer_adress_pf(va_arg(ap, void *), count);
}
