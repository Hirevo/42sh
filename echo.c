/*
** echo.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri May  5 06:44:42 2017 Nicolas Polomack
** Last update Tue May 16 15:54:45 2017 Nicolas Polomack
*/

#include <string.h>
#include <stdio.h>

void	print_char(char *c, int *i)
{
  if (c[*i] == '\\')
    {
      *i += 1;
      if (c[*i] == 'a')
	putchar(0x7);
      else if (c[*i] == 'b')
	putchar(0x8);
      else if (c[*i] == 'f')
	putchar(0xc);
      else if (c[*i] == 'n')
	putchar(0xa);
      else if (c[*i] == 'r')
	putchar(0xd);
      else if (c[*i] == 't')
	putchar(0x9);
      else if (c[*i] == 'v')
	putchar(0xb);
      else if (c[*i] == '\\')
	putchar('\\');
    }
  else
    putchar(c[*i]);
}

int	echo_term(char **args)
{
  int	i;
  int	j;
  int	flag_n;

  flag_n = (args[0] && !strcmp(args[0], "-n"));
  i = flag_n ? 0 : -1;
  while (args[++i])
    {
      if (i - (flag_n))
	putchar(' ');
      j = -1;
      while (args[i][++j])
	print_char(args[i], &j);
    }
  if (!flag_n)
    putchar('\n');
  else
    fflush(stdout);
  return (0);
}
