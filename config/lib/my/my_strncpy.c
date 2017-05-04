/*
** my_strncpy.c for my_strncpy in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:02:03 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:02:04 2017 Arthur Knoepflin
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	count;

  count = 0;
  while (n > 0)
    {
      dest[count] = src[count];
      count = count + 1;
      n = n - 1;
    }
  return (dest);
}
