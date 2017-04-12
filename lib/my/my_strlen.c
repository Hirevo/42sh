/*
** my_strlen.c for my_strlen in /home/nicolas.polomack/CPool_Day04
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Thu Oct  6 10:41:18 2016 Nicolas POLOMACK
** Last update Sat Mar 25 21:49:21 2017 Nicolas Polomack
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (str[count] != 0)
    count = count + 1;
  return (count);
}

int	my_strstrlen(char *str, char *c)
{
  int	i;
  int	e;

  i = -1;
  while (str[++i])
    {
      e = -1;
      while (c[++e])
        if (str[i] == c[e])
          return (i);
    }
  return (i);
}
