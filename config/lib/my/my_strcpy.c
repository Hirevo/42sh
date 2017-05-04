/*
** my_strcpy.c for my_strcpy in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:57:07 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:57:08 2017 Arthur Knoepflin
*/

char	*my_memset(char *buffer, char c, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    buffer[i] = c;
  return (buffer);
}

char	*my_strcpy(char *dest, char *src)
{
  int	count;

  count = -1;
  while (src[++count])
    dest[count] = src[count];
  dest[count] = 0;
  return (dest);
}
