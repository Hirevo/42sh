/*
** my_int_to_char.c for my_int_to_char in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:44:16 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:44:21 2017 Arthur Knoepflin
*/

#include <stdlib.h>

char	*my_int_to_char(int i)
{
  char	*final;
  int	len;
  int	n;

  len = (i <= 0) ? 1 : 0;
  n = (i < 0) ? -i : i;
  while (n >= 1)
    {
      n /= 10;
      len += 1;
    }
  if ((final = malloc(len + 1)) == NULL)
    return (NULL);
  n = (i < 0) ? -1 : 1;
  i *= n;
  final[len--] = 0;
  final[len] = (i == 0) ? 0 + '0' : 0;
  while (i >= 1)
    {
      final[len--] = (i % 10) + '0';
      i /= 10;
    }
  if (len > 0)
    final[0] = '-';
  return (final);
}

char		*my_unsigned_to_char(unsigned int i)
{
  char		*final;
  int		len;
  unsigned int	n;

  len = (i == 0) ? 1 : 0;
  n = i;
  while (n >= 1)
    {
      n /= 10;
      len += 1;
    }
  if ((final = malloc(len + 1)) == NULL)
    return (NULL);
  final[len--] = 0;
  final[len] = (i == 0) ? 0 + '0' : 0;
  while (i >= 1)
    {
      final[len--] = (i % 10) + '0';
      i /= 10;
    }
  return (final);
}
