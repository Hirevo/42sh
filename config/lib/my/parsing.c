/*
** parsing.c for parsing in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:03:25 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:03:25 2017 Arthur Knoepflin
*/

#include "my.h"

char	*get_flags(char *str, t_flags *flags, va_list ap, int *count)
{
  if ((*str == '-') || (*str == '+') || (*str == '0') || (*str == '#') ||
      (*str == ' '))
      flags->hold = *(str++);
  if (*str >= '0' && *str <= '9')
    while (*str >= '0' && *str <= '9')
      flags->width = flags->width * 10 + (*(str++) - '0');
  else if (*str == '*')
    flags->width += va_arg(ap, int) + *(str++) * 0;
  else
    flags->width = -1;
  if (*str == '.')
  {
    if (*(++str) >= '0' && *str <= '9')
      while (*str >= '0' && *str <= '9')
	flags->precision = flags->precision * 10 + (*(str++) - '0');
    else if (*str == '*')
      flags->precision += va_arg(ap, int) + *(str++) * 0;
  }
  else
    str += (flags->precision = ((*str == '.') ? 0 : -1)) + 1;
  if (*str == 'h' || *str == 'l')
    flags->length = *(str++);
  flags->format = *str;
  str = check_parse(str, flags, count);
  return (str);
}

char	*check_parse(char *str, t_flags *flags, int *count)
{
  int	c1;
  int	c2;

  c1 = 0;
  c2 = 0;
  if (flags->format == 'd' || flags->format == 'i' ||
      flags->format == 'p' || flags->format == 'X' || flags->format == 'x' ||
      flags->format == 'o' || flags->format == 'u' || flags->format == 'b' ||
      flags->format == '%' || flags->format == 'd' || flags->format == 'i' ||
      flags->format == 'S' || flags->format == 's' || flags->format == 'c')
    return (str);
  else
  while (*(flags->backup) != flags->format)
    my_putchar_printf(*(flags->backup++), count);
  my_putchar_printf(flags->format, count);
  return (str);
}
