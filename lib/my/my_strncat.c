/*
** my_strncat.c for my_strncat in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:00:30 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:00:31 2017 Arthur Knoepflin
*/

char	*my_strncat(char *dest, char *src, int size)
{
  int	iteration;
  int	i;
  int	c;

  c = 0;
  i = 0;
  iteration = 0;
  while (dest[i] != '\0' && iteration < size)
    {
      i += 1;
      iteration += 1;
    }
  iteration = 0;
  while (src[c] != '\0' && iteration < size)
    {
      dest[i] = src[c];
      c += 1;
      i += 1;
      iteration += 1;
    }
  dest[i] = '\0';
  return (dest);
}
